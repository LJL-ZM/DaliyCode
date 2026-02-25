#pragma once


#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "Protocol.hpp"


#define SERVER_IP inet_addr("43.138.32.230")
#define SERVER_PORT htons(8888)

// 错误枚举
enum NET_ERR
{
    SOCKET_ERR,
    CONNECT_ERR
};

class Sock
{
public:
    Sock() {};

    void Socket()
    {
        socketfd = socket(AF_INET, SOCK_STREAM, 0);
        if (socketfd < 0)
        {
            printf("socket err : %s\n", strerror(errno));
            exit(SOCKET_ERR);
        }
    }

    void Connect()
    {
        sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_addr.s_addr = SERVER_IP;
        server.sin_family = AF_INET;
        server.sin_port = SERVER_PORT;
        int connect_ret = connect(socketfd, (const sockaddr *)(&server), sizeof(server));
        if (connect_ret == -1)
        {
            printf("connect err : %s\n", strerror(errno));
            exit(CONNECT_ERR);
        }
    }
    bool Write(const string &info)
    {
        int write_bytes = write(socketfd, info.c_str(), info.size());
        if (write_bytes <= 0)
        {
            return false;
        }
        return true;
    }
    void Close()
    {
        close(socketfd);
    }
    int Read(std::string &info)
    {
        char read_buf[10240];
        int read_bytes = read(socketfd, read_buf, sizeof(read_buf));
        if (read_bytes < 0)
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
    int socketfd;
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
    // cout << package << endl;
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
    // 反序列化答复
    // cout << info << endl;
    // cout << package << endl;
    if (!Decode(package, info))
    {
        printf("response error\n");
        ret_code = false;
    }
    // cout << info << endl;
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
