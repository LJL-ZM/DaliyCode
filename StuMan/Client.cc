#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <limits>
#include "Protocol.hpp"
#include "ClientSock.hpp"
#include "ClientRegLoginMan.hpp"
#include "ClientStuOpMan.hpp"

using namespace std;


int main()
{
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
    return 0;
}