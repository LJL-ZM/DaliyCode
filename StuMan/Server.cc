#include <iostream>
#include "StuManServer.hpp"
#include "log.hpp"
#include "Daemon.hpp"
#include <stdexcept>
using namespace std;
bool serverStart(){
    try{
        StuManServer &server = StuManServer::getInstance();
        server.Init();
        server.Run();
    }
    catch(...){
        lg(ERROR, "unknow exception!");
        return false;
    }
    return true;
}
int main()
{
    //Daemon::getDaemon().Init();
    // StuManServer& server = StuManServer::getInstance();
    // server.Init();
    // server.Run();
    while (true)
    {
        if(!serverStart()){
            lg(WARN, "server exit exception!");
            sleep(3);
        }
        else{
            lg(INFO, "server exit normal!");
            break;
        }
    }

    return 0;
}