#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <Windows.h>
#include <string>
#include <limits>
#include "WinProtocol.h"
#include "WinClientSock.h"


#define OP_ADD_STUDENT 1   
#define OP_DEL_STUDENT 2   
#define OP_MOD_STUDENT 3   
#define OP_QUERY_STUDENT 4 
#define OP_GET_ALL 5       
#define OP_SORT_SCORE 6    
#define OP_SORT_ID 7       
#define OP_STATISTIC 8     
#define OP_CLEAR_ALL 9     
#define OP_REGISTER 12     
#define OP_LOGIN 13        

#define id_size 10

void menuOpStudent()
{
    printf("****************************************************************\n");
    printf("****            please chose a op you will do               ****\n");
    printf("**** 1 : add_student               2 : del_student_by_id    ****\n");
    printf("**** 3 : mod_student_by_id         4 : find_student_by_id ******\n");
    printf("**** 5 : get_all_student           6 : sort_students_by_score **\n");
    printf("**** 7 : sort_students_by_id       8 : statistics_score ********\n");
    printf("**** 9 : clear_all_students                                 ****\n");
    printf("****    if you are student, you can not to do 1/2/3/9      *****\n");
    printf("****    if you are teacher, you can not to do 9            *****\n");
    printf("****************************************************************\n");
}

void menuOpSort()
{
    printf("****************************************************************\n");
    printf("***** 0 : sort in ascending        1 : sort in decending    ****\n");
    printf("****************************************************************\n");
}

void resetCin()
{
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

bool checkStuName(std::string& name)
{
    name.clear();
    while (!(std::cin >> name))
    {
        printf("Invalid input! Please enter letters only: ");
        resetCin();
    }
    if (name.empty())
    {
        printf("Invalid name (cannot be empty)!\n");
        return false;
    }
    for (auto e : name)
    {
        if (!((e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z')))
        {
            printf("Invalid name (only letters allowed)!\n");
            return false;
        }
    }
    return true;
}

bool checkStuScore(double& score)
{
    score = -1;
    if (!(std::cin >> score))
    {
        printf("Invalid score (must be number)!\n");
        resetCin();
        return false;
    }
    if (score < 0 || score > 100)
    {
        printf("Invalid score (must be 0-100)!\n");
        return false;
    }
    return true;
}

bool checkStuId(std::string& id)
{
    id.clear();
    std::cin >> id;
    resetCin();
    if (id.size() != id_size)
    {
        printf("Invalid id (size must be %d)\n", id_size);
        return false;
    }
    for (auto e : id)
    {
        if (!(e >= '0' && e <= '9')) {
            return false;
        }
    }
    return true;
}

bool stuOp(int role)
{
    menuOpStudent();
    int op_stu;
    if (!(std::cin >> op_stu))
    {
        resetCin();
        printf("Invaild op_stu! Please input number 1-9\n");
        return false;
    }
    if (op_stu < 1 || op_stu > 9)
    {
        printf("Invaild op_stu!\n");
        return false;
    }
    double score = 0;
    std::string order = "-1", id = "", name = "";
    switch (op_stu)
    {
    case 1:
    {
        if (role == 1)
        {
            printf("you are student, permission denied\n");
            return false;
        }
        printf("enter student name that you will add, the name only letters\n");
        if (!checkStuName(name))
        {
            printf("Invalid name!\n");
            resetCin();
            return false;
        }
        printf("enter student score you will add, only 0-100\n");
        if (!checkStuScore(score))
        {
            printf("Invalid score\n");
            resetCin();
            return false;
        }
        printf("enter student id you will add,only numbers and the size only %d\n", id_size);
        if (!checkStuId(id))
        {
            printf("Invalid id\n");
            resetCin();
            return false;
        }
        break;
    }
    case 2:
    {
        if (role == 1)
        {
            printf("you are student, permission denied\n");
            return false;
        }
        printf("enter student id that you will del\n");
        if (!checkStuId(id))
        {
            printf("Invalid id\n");
            return false;
        }
        break;
    }
    case 3:
    {
        if (role == 1)
        {
            printf("you are student, permission denied\n");
            return false;
        }
        printf("enter student id that you will mod\n");
        if (!checkStuId(id))
        {
            printf("Invalid id\n");
            return false;
        }
        printf("enter student name that you will mod\n");
        if (!checkStuName(name))
        {
            printf("Invalid name\n");
            return false;
        }
        printf("enter student score that you will mod\n");
        if (!checkStuScore(score))
        {
            printf("Invalid score\n");
            return false;
        }
        break;
    }
    case 4:
    {
        printf("enter student id that you will find\n");
        if (!checkStuId(id))
        {
            printf("Invalid id\n");
            return false;
        }
        break;
    }
    case 5:
    {
        for (int i = 1; i <= 5; i++)
        {
            printf("loading...\n");
            Sleep(5);
        }
        break;
    }
    case 6:
    case 7:
    {
        menuOpSort();
        int order_tmp = -1;
        std::cin >> order_tmp;
        if (order_tmp != 0 && order_tmp != 1)
        {
            printf("Invaild order!\n");
            return false;
        }
        order = std::to_string(order_tmp);
        break;
    }
    case 8:
    {
        for (int i = 1; i <= 5; i++)
        {
            printf("loading...\n");
            Sleep(5);
        }
        break;
    }
    case 9:
    {
        if (role == 1 || role == 2)
        {
            printf("you are not manager, permission denied\n");
            return false;
        }
        break;
    }
    }
    Sock socket = getSock();
    creatAndSendReq(socket, name, id, std::to_string(op_stu), score, order);
    std::string package, info;
    bool ret_code;
    response reps = ReceiveAndDecode(socket, package, info, ret_code);
    if (!ret_code)
    {
        return false;
    }
    std::cout << reps._meg << std::endl
        << reps._info;
    return true;
}