#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include "Protocol.hpp"
#include "ClientSock.hpp"

#define KEY string("i am manager")


// 操作类型定义
#define OP_ADD_STUDENT 1   // 添加学生
#define OP_DEL_STUDENT 2   // 删除学生
#define OP_MOD_STUDENT 3   // 修改学生
#define OP_QUERY_STUDENT 4 // 按ID查询
#define OP_GET_ALL 5       // 获取所有学生
#define OP_SORT_SCORE 6    // 按成绩排序
#define OP_SORT_ID 7       // 按学号排序
#define OP_STATISTIC 8     // 成绩统计
#define OP_CLEAR_ALL 9     // 清空所有
#define OP_REGISTER 12     // 注册
#define OP_LOGIN 13        // 登录

// 权限身份定义
#define ROLE_STU 1 // 学生
#define ROLE_TEA 2 // 老师
#define ROLE_MAN 3 // 管理员



void menuOpRegistAndLogin()
{
    printf("****      please chose a op, user_regist or user_login?      ****\n");
    printf("****    12 : user_regist                  13 : user_login    ****\n");
    printf("*****************************************************************\n");
}

void menuAboutRole()
{
    printf("****      please chose a role, teacher or student?           ****\n");
    printf("****     1 : student                  2 : teacher            ****\n");
    printf("*****************************************************************\n");
}

int getOp()
{
    menuOpRegistAndLogin();
    int op;
    cin >> op;
    return op;
}

bool checkUsername(std::string &name)
{
    cin >> name;
    int flag = 0;
    if (!(name.size() >= 6 && name.size() <= 18))
    {
        return false;
    }
    for (auto e : name)
    {
        if (!((e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z')))
        {
            return false;
        }
    }
    return true;
}
bool checkPassword(std::string password)
{
    cin >> password;
    int flag = 0;
    if (!(password.size() >= 6 && password.size() <= 18))
    {
        return false;
    }
    for (auto e : password)
    {
        if (!(e >= '0' && e <= '9'))
        {
            return false;
        }
    }
    return true;
}
bool checkRole(int &role)
{
    menuAboutRole();
    cin >> role;
    if (role != ROLE_STU && role != ROLE_TEA && role != ROLE_MAN)
    {
        return false;
    }
    return true;
}
bool checkMan(int role)
{
    if (role == ROLE_MAN)
    {
        printf("if you are manager,please enter the key@");
        fflush(stdout);
        std::string key;
        cin.ignore();
        getline(cin, key);
        if (key != KEY)
        {
            return false;
        }
    }
    return true;
}

bool registe()
{
    std::string name, password;
    int role;
    printf("Please enter your username,Username length must be between 6 and 18 characters,only a-z and A-Z.\n");
    if (!checkUsername(name))
    {
        printf("Invalid username!\n");
        return false;
    }
    // 合法的用户名
    printf("set a password,Password length must be between 6 and 18 characters and contain only numbers.\n");
    if (!checkPassword(password))
    {
        printf("Invalid password!\n");
        return false;
    }
    // 合法的密码
    printf("please enter your role\n");
    if (!checkRole(role))
    {
        printf("Invalid role!\n");
        return false;
    }
    // 是管理员吗？
    if (!checkMan(role))
    {
        printf("you are not manager!\n");
        return false;
    }
    // 网络
    Sock socket = getSock();
    // 构建name+password+role
    // 发送请求
    creatAndSendReq(socket, name, password, to_string(OP_REGISTER), role);
    // 读responce
    std::string package, info;
    bool ret_code;
    response reps = ReceiveAndDecode(socket, package, info, ret_code);
    if (!ret_code)
    {
        return false;
    }
    // 解析是否成功
    cout << reps._meg << endl;
    // cout << reps._confirm_code << endl;
    if (reps._confirm_code != 1)
    {
        // cout << "reps._confirm_code != 1" << endl;
        return false;
    }
    return true;
}

bool login(int &role)
{
    std::string name, password;
    printf("Please enter your username,Username length must be between 6 and 18 characters,only a-z and A-Z.\n");
    if (!checkUsername(name))
    {
        printf("Invalid username!\n");
        return false;
    }
    // 合法的用户名
    printf("enter your password,Password length must be between 6 and 18 characters and contain only numbers.\n");
    if (!checkPassword(password))
    {
        printf("Invalid password!\n");
        return false;
    }
    // 合法的密码
    // 网络
    Sock socket = getSock();
    // 构建name+password+role
    // 发送请求
    creatAndSendReq(socket, name, password, to_string(OP_LOGIN));
    // 读responce
    std::string package, info;
    bool ret_code;
    response reps = ReceiveAndDecode(socket, package, info, ret_code);
    if (!ret_code)
    {
        return false;
    }
    // 解析是否成功
    cout << reps._meg << endl;
    // cout << reps._confirm_code << endl;
    if (reps._confirm_code != 1)
    {
        // cout << "reps._confirm_code != 1" << endl;
        return false;
    }
    role = reps._permission;
    return true;
}