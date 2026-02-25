#pragma once
#include <iostream>
#include <unordered_map>
#include <cstring>
#include <sys/types.h>
#include "log.hpp"
#include "ThreadPoll.hpp"
#include "Protocol.hpp"
#include "Sock.hpp"
#include "Task.hpp"
#include "StudentManager.hpp"

//后续要对共享资源都加锁！！！！！
//改单例
//服务部署
//再拆代码
//初始化时各个文件负责功能再细分

//TODO:
//1.客户端再拆一个文件
//2.task的方法再拆一拆
//3.全面测试
//4.日志一改
//5.部署上线
//6.搞一个Windows版客户端




class StuManServer
{
    const static int poll_num = 10;

    // 构造服务器对象
    StuManServer(u_int16_t port, int threadPollNum = poll_num)
        : _port(port), _threadPoll(threadPollNum)
        ,_is_init(false)
    {
    }
    StuManServer(const StuManServer&) = delete;
    StuManServer& operator=(StuManServer&) = delete;
public:
    static StuManServer& getInstance(){
        if(_ptr == nullptr){
            pthread_mutex_lock(&_static_creat_mutex);
            if(_ptr == nullptr){
                _ptr = new StuManServer(8888);
            }
            pthread_mutex_unlock(&_static_creat_mutex);
        }
        return *_ptr;
    }
    // 初始化服务器
    void Init()
    {
        if(_is_init){
            return;
        }
        pthread_mutex_lock(&_static_creat_mutex);
        if(_is_init){
            pthread_mutex_unlock(&_static_creat_mutex);
            return;
        }
        _listenSock.Socket();
        _listenSock.Bind(_port);
        _listenSock.Listen();
        _threadPoll.run();
        RegLogMan.Init();
        lg(INFO, "RegLogMan init success!");
        Manager.Init();
        lg(INFO, "StuManServer init success...");
        lg(INFO, "server init success!");
        _is_init = true;
        pthread_mutex_unlock(&_static_creat_mutex);
    }
    void Run()
    {
        lg(INFO, "server is running!");
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
    bool _is_init;

    static StuManServer* _ptr;
    static pthread_mutex_t _static_creat_mutex;
};
StuManServer* StuManServer::_ptr = nullptr;
pthread_mutex_t StuManServer::_static_creat_mutex = PTHREAD_MUTEX_INITIALIZER;