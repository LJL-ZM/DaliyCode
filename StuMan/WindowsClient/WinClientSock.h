#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include "WinProtocol.h"

#define SERVER_IP "43.138.32.230"
#define SERVER_PORT 8888

bool InitWSA() {
    WSADATA wsaData;
    int ret = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (ret != 0) {
        printf("WSA初始化失败: %d\n", ret);
        return false;
    }
    return true;
}

enum NET_ERR
{
    SOCKET_ERR,
    CONNECT_ERR,
    WSA_INIT_ERR
};

class Sock
{
public:
    Sock() : socketfd(INVALID_SOCKET) {};
    ~Sock() { if (socketfd != INVALID_SOCKET) Close(); }

    Sock(const Sock&) = delete;
    Sock& operator=(const Sock&) = delete;

    Sock(Sock&& other) noexcept {
        socketfd = other.socketfd;
        other.socketfd = INVALID_SOCKET;
    }

    Sock& operator=(Sock&& other) noexcept {
        if (this != &other) {
            Close();
            socketfd = other.socketfd;
            other.socketfd = INVALID_SOCKET;
        }
        return *this;
    }

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
        server.sin_addr.s_addr = inet_addr(SERVER_IP);
        if (server.sin_addr.s_addr == INADDR_NONE) {
            printf("IP地址格式错误\n");
            exit(CONNECT_ERR);
        }

        int connect_ret = connect(socketfd, (const sockaddr*)(&server), sizeof(server));
        if (connect_ret == SOCKET_ERROR)
        {
            printf("connect err : %d\n", WSAGetLastError());
            exit(CONNECT_ERR);
        }
    }

    bool Write(const std::string& info)
    {
        int total_sent = 0;
        int len = info.size();
        while (total_sent < len) {
            int sent = send(socketfd, info.c_str() + total_sent, len - total_sent, 0);
            if (sent == SOCKET_ERROR)
            {
                printf("发送失败: %d\n", WSAGetLastError());
                return false;
            }
            total_sent += sent;
        }
        return true;
    }

    void Close()
    {
        if (socketfd != INVALID_SOCKET) {
            closesocket(socketfd);
            socketfd = INVALID_SOCKET;
            WSACleanup();
        }
    }

    int ReadAll(std::string& info)
    {
        char read_buf[10240] = { 0 };
        info.clear();
        int total_read = 0;

        while (true) {
            int read_bytes = recv(socketfd, read_buf, sizeof(read_buf) - 1, 0);
            if (read_bytes == SOCKET_ERROR)
            {
                printf("读取失败: %d\n", WSAGetLastError());
                return -1;
            }
            if (read_bytes == 0)
            {
                printf("server refuse\n");
                return 0;
            }
            info.append(read_buf, read_bytes);
            total_read += read_bytes;

            if (info.find(protocol_sem) != std::string::npos) {
                break;
            }
        }
        return total_read;
    }

    bool IsValid() const {
        return socketfd != INVALID_SOCKET;
    }

private:
    SOCKET socketfd;
};

Sock getSock()
{
    if (!InitWSA()) {
        exit(WSA_INIT_ERR);
    }
    Sock socket;
    socket.Socket();
    socket.Connect();
    return socket;
}

const response ReceiveAndDecode(Sock& socket, std::string& package, std::string& info, bool& ret_code)
{
    ret_code = false;
    package.clear();
    info.clear();

    int read_ret = socket.ReadAll(package);
    if (read_ret <= 0) {
        printf("read fail\n");
        socket.Close();
        return response();
    }

    if (!Decode(package, info))
    {
        printf("response error\n");
    }
    else {
        ret_code = true;
    }

    return response(info);
}

void creatAndSendReq(Sock& socket, const std::string& user_name, const std::string& password, const std::string& op_type, int role = 0)
{
    RegLoginRequest req(user_name, password, role, op_type);
    std::string info, package;
    req.Serialize(info);
    package = Encode(info);
    socket.Write(package);
}

void creatAndSendReq(Sock& socket, const std::string& stu_name, const std::string& id, const std::string& op_type, const double& score, const std::string order) {
    StuRequest req(op_type, order, stu_name, id, score);
    std::string info, package;
    req.Serialize(info);
    package = Encode(info);
    socket.Write(package);
}