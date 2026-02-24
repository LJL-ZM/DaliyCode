#include <iostream>
#include "StuManServer.hpp"
#include "log.hpp"
using namespace std;
int main(){
    StuManServer& server = StuManServer::getInstance();
    server.Init();
    server.Run();


    return 0;
}