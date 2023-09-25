## url请求参数

```cpp
#include "wfrest/HttpServer.h"
using namespace wfrest;

int main()
{
    HttpServer svr;

    // /query_list?username=chanchann&password=yyy
    svr.GET("/query_list", [](const HttpReq *req, HttpResp *resp)
    {
        const std::map<std::string, std::string>& query_list = req->query_list();
        for (auto &query: query_list)
        {
            fprintf(stderr, "%s : %s\n", query.first.c_str(), query.second.c_str());
        }
    });

    // /query?username=chanchann&password=yyy
    svr.GET("/query", [](const HttpReq *req, HttpResp *resp)
    {
        const std::string& user_name = req->query("username");
        const std::string& password = req->query("password");
        const std::string& info = req->query("info"); // no this field
        const std::string& address = req->default_query("address", "china");
        resp->String(user_name + " " + password + " " + info + " " + address + "\n");
    });

    // /query_has?username=chanchann&password=
    svr.GET("/query_has", [](const HttpReq *req, HttpResp *resp)
    {
        if (req->has_query("password"))
        {
            fprintf(stderr, "has password query\n");
        }
        if (req->has_query("info"))
        {
            fprintf(stderr, "has info query\n");
        }
    });

    if (svr.start(8888) == 0)
    {
        getchar();
        svr.stop();
    } else
    {
        fprintf(stderr, "Cannot start server");
        exit(1);
    }
    return 0;
}
```
