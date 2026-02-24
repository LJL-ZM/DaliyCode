#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "Protocol.hpp"

#define KEY string("i am manager")
#define SERVER_IP inet_addr("43.138.32.230")
#define SERVER_PORT htons(8888)

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

// 错误枚举
enum NET_ERR
{
    SOCKET_ERR,
    CONNECT_ERR
};

using namespace std;

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
    int Read(string &info)
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

void menuOpStudent()
{
    printf("****************************************************************\n");
    printf("**** 1 : add_student               2 : del_student  ************\n");
    printf("**** 3 : mod_student_by_id         4 : find_student_by_id ******\n");
    printf("**** 5 : get_all_student           6 : sort_students_by_score **\n");
    printf("**** 7 : sort_students_by_id       8 : statistics_score ********\n");
    printf("**** 9 : clear_all_students                                 ****\n");
    printf("****************************************************************\n");
}

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
    int op;
    cin >> op;
    return op;
}

bool checkUsername(string &name)
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
bool checkPassword(string password)
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
        string key;
        cin.ignore();
        getline(cin, key);
        if (key != KEY)
        {
            return false;
        }
    }
    return true;
}
void creatAndSendReq(Sock socket, const string &name, const string &password, const string& op_type,  int role)
{
    RegLoginRequest req(name, password, role, op_type);
    string info, package;
    req.Serialize(info);
    package = Encode(info);
    socket.Write(package);
}
Sock getSock()
{
    Sock socket;
    socket.Socket();
    socket.Connect();
    return socket;
}
const response ReceiveAndDecode(Sock socket, string& package, string& info, bool& ret_code)
{
    //cout << package << endl;
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
    //cout << package << endl;
    if (!Decode(package, info))
    {
        printf("response error\n");
        ret_code = false;
    }
    //cout << info << endl;
    ret_code = true;
    return response(info);
}

int main()
{
    // 选择登录/注册？
    while (true)
    {
        menuOpRegistAndLogin();
        int rl_op = getOp();
        if (rl_op != OP_REGISTER && rl_op != OP_LOGIN)
        {
            continue;
        }
        if (rl_op == OP_REGISTER)
        {
            // 注册
            string name, password;
            int role;
            printf("Please enter your username,Username length must be between 6 and 18 characters,only a-z and A-Z.\n");
            if (!checkUsername(name))
            {
                printf("Invalid username!\n");
                continue;
            }
            // 合法的用户名
            printf("set a password,Password length must be between 6 and 18 characters and contain only numbers.\n");
            if (!checkPassword(password))
            {
                printf("Invalid password!\n");
                continue;
            }
            // 合法的密码
            printf("please enter your role\n");
            if (!checkRole(role))
            {
                printf("Invalid role!\n");
                continue;
            }
            // 是管理员吗？
            if (!checkMan(role))
            {
                printf("you are not manager!\n");
                continue;
            }
            // 网络
            Sock socket = getSock();
            // 构建name+password+role
            // 发送请求
            creatAndSendReq(socket, name, password, to_string(rl_op), role);
            // 读responce
            string package, info;
            bool ret_code;
            response reps = ReceiveAndDecode(socket, package, info, ret_code);
            if(!ret_code){
                continue;
            }
            //解析是否成功
            cout << reps._meg << endl;
            //cout << reps._confirm_code << endl;
            if (reps._confirm_code != 1)
            {
                cout << "reps._confirm_code != 1" << endl;
                continue;
            }
        }
    }
    // 注册：构建一个注册请求+发给服务端（注册必须合法（内容合法+注册成功））---if

    // 登录：构建一个登录请求+发给服务端（登录请求必须合法（内容合法++密码正确+获取权限））

    // 死循环---打印菜单+本地测试权限+发起请求+读回复+打印结果

    return 0;
}