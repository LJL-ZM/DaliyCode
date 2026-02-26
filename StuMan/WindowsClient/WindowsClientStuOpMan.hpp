#pragma once

#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <limits>
#include "Protocol.hpp"
#include "ClientSock.hpp"

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
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool checkStuName(std::string &name)
{
    name.clear();
    while (!(cin >> name)) 
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

bool checkStuScore(double &score)
{
    score = -1; 
    if (!(cin >> score))
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

bool checkStuId(std::string &id)
{
    id.clear();
    cin >> id;
    resetCin(); 
    if (id.size() != id_size)
    {
        printf("Invalid id (size must be %d)\n", id_size);
        return false;
    }
    for (auto e : id)
    {
        if (!(e >= '0' && e <= '9')){
            return false;
        }
    }
    return true;
}

bool stuOp(int role)
{
    menuOpStudent();
    // 输入+构建请求
    int op_stu;
    if (!(cin >> op_stu))
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
            Sleep(50);
        }
        break;
    }
    case 6:
    case 7:
    {
        menuOpSort();
        int order_tmp = -1;
        cin >> order_tmp;
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
            Sleep(50);
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
    // 构建并发送请求
    Sock socket = getSock();
    creatAndSendReq(socket, name, id, std::to_string(op_stu), score, order);
    // 接收并且解析答复
    std::string package, info;
    bool ret_code;
    response reps = ReceiveAndDecode(socket, package, info, ret_code);
    if (!ret_code)
    {
        return false;
    }
    cout << reps._meg << endl
         << reps._info;
    return true;
}