#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "Protocol.hpp"

#define SERVER_IP "43.138.32.230"
#define SERVER_PORT 8888

// 错误枚举
enum NET_ERR
{
    SOCKET_ERR,
    CONNECT_ERR
};

class Sock
{
public:
    Sock() : socketfd(INVALID_SOCKET) {};
    ~Sock() { if (socketfd != INVALID_SOCKET) Close(); }

    void Socket()
    {
        socketfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (socketfd == INVALID_SOCKET)
        {
            printf("socket err : %d\n", WSAGetLastError());
            exit(SOCKET_ERR);
        }
    }

    void Connect()
    {
        sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_port = htons(SERVER_PORT);
        inet_pton(AF_INET, SERVER_IP, &server.sin_addr);
        
        int connect_ret = connect(socketfd, (const sockaddr *)(&server), sizeof(server));
        if (connect_ret == SOCKET_ERROR)
        {
            printf("connect err : %d\n", WSAGetLastError());
            exit(CONNECT_ERR);
        }
    }
    bool Write(const string &info)
    {
        int write_bytes = send(socketfd, info.c_str(), info.size(), 0);
        if (write_bytes == SOCKET_ERROR)
        {
            return false;
        }
        return true;
    }
    void Close()
    {
        closesocket(socketfd);
        socketfd = INVALID_SOCKET;
    }
    int Read(std::string &info)
    {
        char read_buf[10240] = {0};
        int read_bytes = recv(socketfd, read_buf, sizeof(read_buf) - 1, 0);
        if (read_bytes == SOCKET_ERROR)
        {
            return -1;
        }
        if (read_bytes == 0)
        {
            return 0;
        }
        info = read_buf;
        return 1;
    }

private:
    SOCKET socketfd;
};

Sock getSock()
{
    Sock socket;
    socket.Socket();
    socket.Connect();
    return socket;
}

const response ReceiveAndDecode(Sock socket, std::string &package, std::string &info, bool &ret_code)
{
    switch (socket.Read(package))
    {
    case -1:
        printf("read fail\n");
        socket.Close();
        ret_code = false;
        break;
    case 0:
        printf("server refuse\n");
        socket.Close();
        ret_code = false;
        break;
    default:
        break;
    }
    if (!Decode(package, info))
    {
        printf("response error\n");
        ret_code = false;
    }
    ret_code = true;
    return response(info);
}

void creatAndSendReq(Sock socket, const std::string &user_name, const std::string &password, const string &op_type, int role = 0)
{
    RegLoginRequest req(user_name, password, role, op_type);
    string info, package;
    req.Serialize(info);
    package = Encode(info);
    socket.Write(package);
}

void creatAndSendReq(Sock socket, const std::string &stu_name, const std::string& id, const string& op_type, const double& score, const std::string order){
    StuRequest req(op_type, order, stu_name, id, score);
    string info, package;
    req.Serialize(info);
    package = Encode(info);
    socket.Write(package);
}