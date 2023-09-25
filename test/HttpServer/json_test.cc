#include <gtest/gtest.h>
#include "wfrest/HttpServer.h"
#include "wfrest/Json.h"
#include "workflow/WFFacilities.h"

using namespace wfrest;
using namespace protocol;

WFHttpTask *create_http_task(const std::string &path)
{
    return WFTaskFactory::create_http_task("http://127.0.0.1:8888/" + path, 4, 2, nullptr);
}

TEST(JsonTest, json)
{
    HttpServer svr;
    WFFacilities::WaitGroup wait_group(1);

    svr.GET("/test", [](const HttpReq *req, HttpResp *resp)
    {
        Json json;
        json["test"] = 123;
        json["json"] = "test json";
        resp->Json(json);
    });

    EXPECT_TRUE(svr.start("127.0.0.1", 8888) == 0) << "http server start failed";

    WFHttpTask *client_task = create_http_task("test");
    client_task->set_callback([&wait_group](WFHttpTask *task)
    {
        HttpResponse *resp = task->get_resp();

        HttpHeaderMap header(resp);
        std::string content_type = header.get("Content-Type");
        EXPECT_EQ(content_type, "application/json");

        const void *body;
        size_t body_len;
        resp->get_parsed_body(&body, &body_len);
        std::string json_str(static_cast<const char *>(body), body_len);
        Json js = Json::parse(json_str);
        EXPECT_EQ(js["test"].get<int>(), 123);
        EXPECT_EQ(js["json"].get<std::string>(), "test json");
        wait_group.done();
    });

    client_task->start();
    wait_group.wait();
    svr.stop();
}

TEST(JsonTest, valid_str)
{
    HttpServer svr;
    WFFacilities::WaitGroup wait_group(1);

    svr.GET("/test", [](const HttpReq *req, HttpResp *resp)
    {
        std::string valid_text = R"(
        {
            "numbers": [1, 2, 3]
        }
        )";
        resp->Json(valid_text);
    });
    EXPECT_TRUE(svr.start("127.0.0.1", 8888) == 0) << "http server start failed";

    WFHttpTask *client_task = create_http_task("test");
    client_task->set_callback([&wait_group](WFHttpTask *task)
    {
        HttpResponse *resp = task->get_resp();

        HttpHeaderMap header(resp);
        std::string content_type = header.get("Content-Type");
        EXPECT_TRUE(content_type == "application/json");

        const void *body;
        size_t body_len;
        resp->get_parsed_body(&body, &body_len);

        std::string json_str(static_cast<const char *>(body), body_len);
        Json js = Json::parse(json_str);
        auto res = js["numbers"].get<Json::Array>();
        // TODO : NOT return reference, so can't do it like this
        // EXPECT_EQ(res[0].get<int>, 1);
        // EXPECT_EQ(res[1].get<int>, 2);
        // EXPECT_EQ(res[2].get<int>, 3);
        wait_group.done();
    });

    client_task->start();
    wait_group.wait();
    svr.stop();
}

TEST(JsonTest, invalid_str)
{
    HttpServer svr;
    WFFacilities::WaitGroup wait_group(1);

    svr.GET("/test", [](const HttpReq *req, HttpResp *resp)
    {
        std::string invalid_text = R"(
        {
            "strings": ["extra", "comma", ]
        }
        )";
        resp->Json(invalid_text);
    });

    EXPECT_TRUE(svr.start("127.0.0.1", 8888) == 0) << "http server start failed";

    WFHttpTask *client_task = create_http_task("test");
    client_task->set_callback([&wait_group](WFHttpTask *task)
    {
        HttpResponse *resp = task->get_resp();

        HttpHeaderMap header(resp);
        std::string content_type = header.get("Content-Type");
        EXPECT_TRUE(content_type == "application/json");

        const void *body;
        size_t body_len;
        resp->get_parsed_body(&body, &body_len);

        std::string json_str(static_cast<const char *>(body), body_len);
        Json js = Json::parse(json_str);
        EXPECT_EQ(js["errmsg"].get<std::string>(), "Invalid Json Syntax");
        wait_group.done();
    });

    client_task->start();
    wait_group.wait();
    svr.stop();
}

TEST(JsonTest, recv_json)
{
    HttpServer svr;
    WFFacilities::WaitGroup wait_group(1);

    svr.POST("/test", [](const HttpReq *req, HttpResp *resp)
    {
        if (req->content_type() != APPLICATION_JSON)
        {
            std::string err_json(R"({errmsg : "Content Type not APPLICATION_JSON"})");
            resp->Json(err_json);
            return;
        }
        const std::string& body = req->body();
        Json js = Json::parse(body);
        EXPECT_EQ(req->header("Content-Type"), "application/json");
        EXPECT_EQ(js["test"].get<int>(), 123);
        EXPECT_EQ(js["recv"].get<std::string>(), "json");
    });

    EXPECT_TRUE(svr.start("127.0.0.1", 8888) == 0) << "http server start failed";

    WFHttpTask *client_task = create_http_task("test");
    client_task->set_callback([&wait_group](WFHttpTask *task)
    {
        delete static_cast<std::string *>(task->user_data);
        wait_group.done();
    });
    Json js;
    js["test"] = 123;
    js["recv"] = "json";
    std::string js_str = js.dump();
    std::string *str = new std::string;
    *str = std::move(js_str);
    client_task->get_req()->set_method("POST");
    client_task->get_req()->append_output_body_nocopy(str->data(), str->size());
    client_task->get_req()->add_header_pair("Content-Type", "application/json");
    client_task->user_data = str;
    client_task->start();
    wait_group.wait();
    svr.stop();
}
