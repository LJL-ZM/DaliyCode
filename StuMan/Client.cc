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
#include "ClientRegLoginMan.hpp"

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
using namespace std;

void menuOpStudent()
{
    printf("****************************************************************\n");
    printf("****            please chose a op you will do               ****\n");
    printf("**** 1 : add_student               2 : del_student_by_id    ****\n");
    printf("**** 3 : mod_student_by_id         4 : find_student_by_id ******\n");
    printf("**** 5 : get_all_student           6 : sort_students_by_score **\n");
    printf("**** 7 : sort_students_by_id       8 : statistics_score ********\n");
    printf("**** 9 : clear_all_students                                 ****\n");
    printf("****************************************************************\n");
}

void menuOpSort()
{
    printf("****************************************************************\n");
    printf("***** 0 : sort in ascending        1 : sort in decending    ****\n");
    printf("****************************************************************\n");
}

void resetCin(bool ignore_newline = false)
{
    cin.clear(); 
    if (ignore_newline) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

bool checkStuName(std::string &name)
{
    resetCin();
    std::getline(std::cin, name);
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
    resetCin(); 
    if (!(cin >> score))
    {
        printf("Invalid score (must be number)!\n");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    if (score < 0 || score > 100)
    {
        printf("Invalid score (must be 0-100)!\n");
        cin.ignore(1, '\n'); 
        return false;
    }
    cin.ignore(1, '\n'); 
    return true;
}

bool checkStuId(std::string &id)
{
    resetCin();
    std::cin >> id;  
    if (id.size() != id_size)
    {
        printf("Invalid id (size must be %d)\n", id_size);
        return false;
    }
    for (auto e : id)
    {
        if (!(e >= '0' && e <= '9'))
            return false;
    }
    return true;
}

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
        menuOpStudent();
        // 输入+构建请求
        //  #define OP_SORT_SCORE 6    // 按成绩排序
        //  #define OP_SORT_ID 7       // 按学号排序
        int op_stu;
        if (!(cin >> op_stu))
        {
            resetCin(); 
            printf("Invaild op_stu! Please input number 1-9\n");
            continue;
        }
        resetCin(true);
        if (op_stu < 1 || op_stu > 9)
        {
            printf("Invaild op_stu!\n");
            continue;
        }
        // **** 1 : add_student               2 : del_student  ************
        // **** 3 : mod_student_by_id         4 : find_student_by_id ******
        // **** 5 : get_all_student           6 : sort_students_by_score **
        // **** 7 : sort_students_by_id       8 : statistics_score ********
        // **** 9 : clear_all_students                                 ****
        double score = 0;
        std::string order = "-1", id = "", name = "";
        switch (op_stu)
        {
        case 1:
        {
            printf("enter student name that you will add, the name only letters\n");
            if (!checkStuName(name))
            {
                printf("Invalid name!\n");
                resetCin();
                continue;
            }
            printf("enter student score you will add, only 0-100\n");
            if (!checkStuScore(score))
            {
                printf("Invalid score\n");
                resetCin();
                continue;
            }
            printf("enter student id you will add,only numbers and the size only %d\n", id_size);
            if (!checkStuId(id))
            {
                printf("Invalid id\n");
                resetCin();
                continue;
            }
            break;
        }
        case 2:
        {
            printf("enter student id that you will del\n");
            if (!checkStuId(id))
            {
                printf("Invalid id\n");
                continue;
            }
            break;
        }
        case 3:
        {
            printf("enter student id that you will mod\n");
            if (!checkStuId(id))
            {
                printf("Invalid id\n");
                continue;
            }
            printf("enter student name that you will mod\n");
            if (!checkStuName(name))
            {
                printf("Invalid name\n");
                continue;
            }
            printf("enter student score that you will mod\n");
            if (!checkStuScore(score))
            {
                printf("Invalid score\n");
                continue;
            }
            break;
        }
        case 4:
        {
            printf("enter student id that you will find\n");
            if (!checkStuId(id))
            {
                printf("Invalid id\n");
                continue;
            }
            break;
        }
        case 5:
        {
            for (int i = 1; i <= 5; i++)
            {
                printf("loading...\n");
                usleep(50000);
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
                continue;
            }
            order = std::to_string(order_tmp);
            break;
        }
        case 8:
        {
            for (int i = 1; i <= 5; i++)
            {
                printf("loading...\n");
                usleep(50000);
            }
            break;
        }
        case 9:
        {

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
            continue;
        }
        cout << reps._meg << endl
             << reps._info;
    }
    return 0;
}