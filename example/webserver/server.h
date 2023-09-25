#ifndef __SERVER_H_
#define __SERVER_H_
#include "workflow/WFFacilities.h"
#include "wfrest/HttpServer.h"

class WebServer {
public:
    WebServer();
    void Run();
    void Init();
    void RegisterRouter(std::string type, std::string route, wfrest::Handler callback);
private:
    wfrest::HttpServer svr_;
};

#endif