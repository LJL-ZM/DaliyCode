#pragma once
#include <iostream>
#include "log.hpp"
#include "ThreadPoll.hpp"
#include "Protocol.hpp"
#include "Sock.hpp"
#include "Task.hpp"
#include <sys/types.h>

class Server{
    const static int poll_num = 10;
public:
    //构造服务器对象
    Server(u_int16_t port, int threadPollNum = poll_num)
    :_port(_port)
    ,_threadPoll(threadPollNum){
        _threadPoll.run();
    }
    //初始化服务器
    void Init(){
        _listenSock.Socket();
        _listenSock.Bind(_port);
        _listenSock.Listen();
        lg(INFO, "StuManServer init success...");
    }
    void Run(){
        while(true){
            string clientIp;
            int clientPort;
            int socketid = _listenSock.Accept(clientIp, clientPort);
            lg(INFO, "get a new link [%s:%d]", clientIp.c_str(), clientPort);
            char request[SIZE];
            read(socketid, request, sizeof(request));
              
        }
    }
private:
    Sock _listenSock;
    u_int16_t _port;
    ThreadPoll<Task> _threadPoll;
};