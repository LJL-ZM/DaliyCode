#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <limits>
#include "WinProtocol.h"
#include "WinClientSock.h"
#include "WinClientRegLoginMan.h"
#include "WinClientStuOpMan.h"

using namespace std;

int main()
{
    // 初始化Winsock2
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed! Error code: %d\n", WSAGetLastError());
        return 1;
    }

    // 选择登录/注册？
    int role = 0;
    while (true)
    {
        int rl_op = getOp();
        if (rl_op != OP_REGISTER && rl_op != OP_LOGIN)
        {
            continue;
        }
        if (rl_op == OP_REGISTER)
        {
            // 注册
            bool reg_ret = registe();
            if (!reg_ret)
            {
                continue;
            }
            // 注册成功
        }
        else if (rl_op == OP_LOGIN)
        {
            // 登录
            bool login_ret = login(role);
            if (!login_ret)
            {
                continue;
            }
            else
            {
                break;
            }
            // cout << role << endl;
        }
    }
    // 登录成功
    // 循环---打印菜单+本地测试权限+发起请求+读回复+打印结果
    while (true)
    {
        stuOp(role);
    }

    // 清理Winsock
    WSACleanup();
    return 0;
}