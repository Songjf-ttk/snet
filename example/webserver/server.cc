#include "server.h"
#include "util.h"

WebServer::WebServer() {
    svr_.ROUTE("/404", [](const wfrest::HttpReq *req, wfrest::HttpResp *resp)
    {
        std::string method(req->get_method());
        resp->add_header("Access-Control-Allow-Origin", "*");
        resp->String(std::move(method) + " 404 not found\n");
    }, {"GET", "POST"});
    svr_.set_default_route("/404");
}

void WebServer::Run()
{
    if (svr_.track().start(8000) == 0)
    {
        svr_.list_routes();
        getchar();
        svr_.stop();
    } else 
    {
        fprintf(stderr, "Cannot satrt server");
        exit(1);
    }
}

void WebServer::RegisterRouter(std::string type, std::string route, wfrest::Handler callback)
{
    if(type == "POST")
    {
        svr_.ROUTE(route, callback, {"POST", "OPTIONS"});
    } else if(type == "GET")
    {
        svr_.ROUTE(route, callback, {"GET", "OPTIONS"});
    }else 
    {
        svr_.ROUTE(route, callback, {"GET", "POST", "OPTINOS"});
    }
}

void WebServer::Init()
{
    RegisterRouter("POST", "/login", Login);
    RegisterRouter("POST", "/logout", Logout);
    RegisterRouter("POST", "/signin", Signin);
    RegisterRouter("POST", "/signinpre", SigninPre);
    RegisterRouter("POST", "/reset-password", ResetPassword);
    RegisterRouter("POST", "/produce-paper", ProducePaper);
    RegisterRouter("GET", "/get-question/{questionId}", GetQuesion);
    RegisterRouter("GET", "/get-score", GetScore);
}