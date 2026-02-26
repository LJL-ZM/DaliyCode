#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include "WinProtocol.h"
#include "WinClientSock.h"

#define KEY std::string("i am manager")


#define OP_ADD_STUDENT 1   
#define OP_DEL_STUDENT 2   
#define OP_MOD_STUDENT 3   
#define OP_QUERY_STUDENT 4 
#define OP_GET_ALL 5       
#define OP_SORT_SCORE 6    
#define OP_SORT_ID 7       
#define OP_STATISTIC 8     
#define OP_CLEAR_ALL 9     
#define OP_REGISTER 12     
#define OP_LOGIN 13        


#define ROLE_STU 1 
#define ROLE_TEA 2 
#define ROLE_MAN 3 

void menuOpRegistAndLogin()
{
    printf("*****************************************************************\n");
    printf("****      please chose a op, user_regist or user_login?      ****\n");
    printf("****    12 : user_regist                  13 : user_login    ****\n");
    printf("*****************************************************************\n");
}

void menuAboutRole()
{
    printf("*****************************************************************\n");
    printf("****      please chose a role, teacher or student?           ****\n");
    printf("****     1 : student                  2 : teacher            ****\n");
    printf("*****************************************************************\n");
}

int getOp()
{
    menuOpRegistAndLogin();
    int op;
    std::cin >> op;
    return op;
}

bool checkUsername(std::string& name)
{
   std::cin >> name;
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
    std::cin >> password;
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
bool checkRole(int& role)
{
    menuAboutRole();
    std::cin >> role;
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
        std::cin.ignore();
        std::getline(std::cin, key);
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

    printf("set a password,Password length must be between 6 and 18 characters and contain only numbers.\n");
    if (!checkPassword(password))
    {
        printf("Invalid password!\n");
        return false;
    }
  
    printf("please enter your role\n");
    if (!checkRole(role))
    {
        printf("Invalid role!\n");
        return false;
    }

    if (!checkMan(role))
    {
        printf("you are not manager!\n");
        return false;
    }
  
    Sock socket = getSock();
    

    creatAndSendReq(socket, name, password, std::to_string(OP_REGISTER), role);
    // 读responce
    std::string package, info;
    bool ret_code;
    response reps = ReceiveAndDecode(socket, package, info, ret_code);
    if (!ret_code)
    {
        return false;
    }
    //TODO


    /*std::cout <<"msg:" << reps._meg << std::endl;
    std::cout <<"confirm_code:" << reps._confirm_code << std::endl;*/
    if (reps._confirm_code != 1)
    {
        return false;
    }
    return true;
}

bool login(int& role)
{
    std::string name, password;
    printf("Please enter your username,Username length must be between 6 and 18 characters,only a-z and A-Z.\n");
    if (!checkUsername(name))
    {
        printf("Invalid username!\n");
        return false;
    }
   
    printf("enter your password,Password length must be between 6 and 18 characters and contain only numbers.\n");
    if (!checkPassword(password))
    {
        printf("Invalid password!\n");
        return false;
    }
    Sock socket = getSock();
    creatAndSendReq(socket, name, password, std::to_string(OP_LOGIN));
    // 读responce
    std::string package, info;
    bool ret_code;
    response reps = ReceiveAndDecode(socket, package, info, ret_code);
    if (!ret_code)
    {
        return false;
    }
    std::cout << reps._meg << std::endl;
    if (reps._confirm_code != 1)
    {
        return false;
    }
    role = reps._permission;
    return true;
}