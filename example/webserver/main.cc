#include "server.h"

int main()
{
    WebServer server;
    server.Init();
    server.Run();
    return 0;
}