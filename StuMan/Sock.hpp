#pragma once
#define LISTEN_LEN 10

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "log.hpp"
#include <cstring>

extern Log lg;
enum{
    SOCK_ERR,
    BIND_ERR,
};

class Sock{
public:
    Sock(){}
    void Socket()
    {
        _listenfd = socket(AF_INET, SOCK_STREAM, 0);
        if(_listenfd <= 0){
            lg(FATAL, "socket err,str : %s", strerror(errno));
            exit(SOCK_ERR);
        }
        int opt = 1;
        setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    }
    void Bind(u_int16_t port)
    {
        sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_addr.s_addr = inet_addr("0.0.0.0");
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        int bind_ret = bind(_listenfd, (const sockaddr*)(&server), sizeof(server));
        if(bind_ret == -1){
            lg(FATAL, "bind err,str : %s", strerror(errno));
            exit(BIND_ERR);
        }
    }
    void Listen(){
        int listen_ret = listen(_listenfd, LISTEN_LEN);
        if(listen_ret == -1){
            lg(WARN, "listen err,str : %s", strerror(errno));
        }
    }
    int Accept(string& ip, int& port){
        sockaddr_in client;
        memset(&client, 0, sizeof(client));
        socklen_t len = sizeof(client);
        int socket = accept(_listenfd, (sockaddr*)(&client), &len);
        if(socket < 0){
            lg(WARN, "accept err,str : %s", strerror(errno));
        }
        fromNetToh(client, ip, port);
        return socket;
    }
    void Connect(int sockfd, const char* ip, u_int16_t port){
        sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_addr.s_addr = inet_addr(ip);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        int connect_ret = connect(_listenfd, (const sockaddr*)(&server), sizeof(server));
        if(connect_ret < 0){
            lg(WARN, "connect err,str : %s", strerror(errno));
        }
    }
    void fromNetToh(const sockaddr_in& in, std::string& ip, int& port){
        ip = inet_ntoa(in.sin_addr);
        port = ntohs(in.sin_port);
    }
    int Get_Sock(){
        return _listenfd;
    }
    ~Sock(){
        close(_listenfd);
    }
private:
    int _listenfd;
};