#include <iostream>
#include "StuManServer.hpp"
#include "log.hpp"
using namespace std;
int main(){
    StuManServer server(8888);
    server.Init();
    lg(INFO, "server init success!");
    server.Run();


    return 0;
}