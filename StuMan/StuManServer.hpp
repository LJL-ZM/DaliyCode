#pragma once
#include <iostream>
#include "log.hpp"
#include "ThreadPoll.hpp"
#include "Protocol.hpp"
#include "Sock.hpp"
#include "Task.hpp"
#include "StudentManager.hpp"
#include <sys/types.h>
#include <cstring>

extern Log lg;
extern StudentManager Manager;

class StuManServer
{
    const static int poll_num = 10;

public:
    // 构造服务器对象
    StuManServer(u_int16_t port, int threadPollNum = poll_num)
        : _port(port), _threadPoll(threadPollNum)
    {
    }
    // 初始化服务器
    void Init()
    {
        _listenSock.Socket();
        _listenSock.Bind(_port);
        _listenSock.Listen();
        _threadPoll.run();
        Manager.readFromBinFile();
        lg(INFO, "StuManServer init success...");
    }
    void Run()
    {
        while (true)
        {
            string clientIp;
            int clientPort;
            int socketid = _listenSock.Accept(clientIp, clientPort);
            lg(INFO, "get a new link [%s:%d]", clientIp.c_str(), clientPort);
            Task task(socketid, clientIp, clientPort);
            _threadPoll.push(task);
        }
    }

private:
    Sock _listenSock;
    u_int16_t _port;
    ThreadPoll<Task> _threadPoll;
};