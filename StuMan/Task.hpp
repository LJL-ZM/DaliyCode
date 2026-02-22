#pragma once

#include <iostream>
#include <memory>
#include "Protocol.hpp"
#include "log.hpp"
#include "StudentManager.hpp"
#include "RegLoginMan.hpp"

extern Log lg;
extern StudentManager Manager;
extern RegLoginMan RegLogMan;
class Task
{
private:
    unique_ptr<BaseRequest> createRequest(int op_type) const
    {
        // 注册登录
        if (op_type == OP_REGISTER || op_type == OP_LOGIN)
        {
            return unique_ptr<RegLoginRequest>();
        }
        // 其它
        else
        {
            return unique_ptr<StuRequest>();
        }
    }

public:
    Task(const int &socketfd, const std::string &clientip, u_int16_t clientport)
        : _socketfd(socketfd), _clientip(clientip), _clientport(clientport), _req_ptr(nullptr)
    {
    }

    bool initTask()
    {
        char request_buf[SIZE];
        std::string req; // 消息全部读取进req
        int cnt = 0, flag = 0;
        while (true)
        {
            cnt++;
            int read_bytes = read(_socketfd, request_buf, sizeof(request_buf));
            if (read_bytes < 0)
            {
                lg(ERROR, "read fail with [%s:%d], err str:%s", _clientip.c_str(), _clientport, strerror(errno));
                flag = 1;
                break;
            }
            else if (read_bytes == 0)
            {
                if (cnt == 1)
                {
                    lg(ERROR, "read fail with [%s:%d], err str:%s", _clientip.c_str(), _clientport, strerror(errno));
                    flag = 1;
                    break;
                }
                else
                {
                    break;
                }
            }
            else
            {
                req.append(request_buf, read_bytes);
                continue;
            }
        }
        if (flag)
        {
            close(_socketfd);
            return false;
        }
        // 读到了一条消息
        std::string req_package = req, info;
        if (!Decode(req_package, info))
        {
            // 解码失败
            close(_socketfd);
            lg(WARN, "Decode fail in community with [%s:%d], err str:%s", _clientip.c_str(), _clientport, strerror(errno));
            return false;
        }
        // 临时解析op，由此判断如何初始化req
        Json::Value root;
        Json::Reader r;
        if (!r.parse(info, root))
        {
            // 解析失败
            close(_socketfd);
            lg(WARN, "Parse op_type fail with [%s:%d]", _clientip.c_str(), _clientport);
            return false;
        }
        // 解析op成功，由此实例化req
        int op_type = -1;
        op_type = std::stoi(root["_op_type"].asString());
        if (op_type == -1)
        {
            close(_socketfd);
            lg(WARN, "have no op_type with [%s:%d]", _clientip.c_str(), _clientport);
            return false;
        }
        // 创建对应请求子类
        _req_ptr = createRequest(op_type);
        if (!_req_ptr)
        {
            close(_socketfd);
            lg(WARN, "Unsupported op_type [%d] from [%s:%d]", op_type, _clientip.c_str(), _clientport);
            return false;
        }

        // 反序列化到对应子类
        if (!_req_ptr->DeSerialize(info))
        {
            close(_socketfd);
            lg(WARN, "DeSerialize fail with [%s:%d]", _clientip.c_str(), _clientport);
            return false;
        }
    }

    void operator()()
    {
        std::string meg, info;
        if (initTask())
        {
            int op = _req_ptr->GetOp();
            switch (op)
            {
            case OP_ADD_STUDENT:
            {
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                if (Manager.insertStudent(st))
                {
                    // 将答复描述和需要发送的消息序列化好写进_reps中
                    meg = "insertStudent success!";
                    info = "";
                }
                else
                {
                    // 添加学生失败
                    meg = "insertSuccess fail, Student ID duplicate or no memory, contact admin!";
                    info = "";
                }
                break;
            }
            case OP_DEL_STUDENT:
            {
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                if (Manager.deleteStudent(st.id))
                {
                    // 删除成功
                    meg = "delete success!";
                    info = "";
                }
                else
                {
                    // 删除学生失败
                    meg = "delete fail, target student does not exist!";
                    info = "";
                }
                break;
            }
            case OP_MOD_STUDENT:
            {
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                if (Manager.modifyStudent(st.id, st.name, st.score))
                {
                    meg = "modify success!";
                    info = "";
                }
                else
                {
                    // 修改学生失败
                    meg = "modefy fail, target student dose not exist!";
                    info = "";
                }
                break;
            }
            case OP_QUERY_STUDENT:
            {
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                Student *s = Manager.findStudentById(st.id);
                if (s)
                {
                    // 查到
                    meg = "find success!";
                    info = s->id;
                    info += " ";
                    info += s->name;
                    info += " ";
                    char score_buf[32];
                    snprintf(score_buf, sizeof(score_buf), "%.2f", s->score);
                    info += score_buf;
                    info += '\n';
                }
                else
                {
                    // 没查到
                    meg = "not found!";
                    info = "";
                }
                break;
            }
            case OP_GET_ALL:
            {
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                std::vector<Student> all_students = Manager.getAllStudents();
                if (!all_students.empty())
                {
                    // 接收vector并且转为string
                    meg = "there are " + to_string(all_students.size()) + "students in the system!";
                    for (auto e : all_students)
                    {
                        info += e.id;
                        info += " ";
                        info += e.name;
                        info += " ";
                        char score_buf[32];
                        snprintf(score_buf, sizeof(score_buf), "%.2f", e.score);
                        info += score_buf;
                        info += '\n';
                    }
                }
                else
                {
                    // 无学生数据
                    meg = "there are 0 students in the systeam!";
                    info = "";
                }
            }
            break;
            case OP_SORT_SCORE:
            {
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                int score_order = std::stoi(_req._order.c_str());
                if (Manager.sortByScore(score_order))
                {
                    meg = "sort success!";
                    info = "";
                }
                else
                {
                    // 排序失败
                    meg = "cannot sort!";
                }
                break;
            }
            case OP_SORT_ID:{
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                int id_order = std::stoi(_req._order.c_str());
                if (Manager.sortById(id_order))
                {
                    meg = "sort success!";
                    info = "";
                }
                else
                {
                    // 排序失败
                    meg = "cannot sort!";
                    info = "";
                }
                break;
            }
            case OP_STATISTIC:{
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                int totalCount, excellent, fail;
                float avgScore, maxScore, minScore;
                if (Manager.scoreStatistics(totalCount, avgScore, maxScore, minScore, excellent, fail))
                {
                    char avg_buf[32], max_buf[32], min_buf[32];
                    snprintf(avg_buf, sizeof(avg_buf), "%.2f", avgScore);
                    snprintf(max_buf, sizeof(max_buf), "%.2f", maxScore);
                    snprintf(min_buf, sizeof(min_buf), "%.2f", minScore);
                    info += std::to_string(totalCount) + " ";
                    info += avg_buf;
                    info += " ";
                    info += max_buf;
                    info += " ";
                    info += std::to_string(excellent);
                    info += " ";
                    info += std::to_string(fail);
                    info += '\n';
                }
                else
                {
                    // 统计失败
                    meg = "have no data!";
                    info = "";
                }
                break;
            }
            case OP_CLEAR_ALL:{
                auto &_req = static_cast<StuRequest &>(*_req_ptr);
                Student st(_req._id, _req._name, _req._score);
                if (Manager.clearAllStudents())
                {
                    meg = "clear all student success!";
                    info = "";
                }
                else
                {
                    // 清空学生失败
                    meg = "have no student";
                    info = "";
                }
                break;
            }
            case OP_REGISTER:{
                //注册
                auto &_req = static_cast<RegLoginRequest&>(*_req_ptr);
                int RegisterRet = RegLogMan.Register(_req._ip, _req._user_name, _req._password, _req._role);
                if(RegisterRet == UNKNOWN_ERR){
                    meg = "Unknown err, contact admin!";
                    info = "";
                }
                else if(RegisterRet == REG_FILE_ERR){
                    meg = "reg file fail, contact admin!";
                    info = "";
                }
                else if(RegisterRet == REG_EXIST){
                    meg = "reg exist, login!";
                    info = "";
                }
                else if(RegisterRet == REG_SUCCESS){
                    meg = "Registe success!";
                    info = "";
                }
            }
            case OP_LOGIN:{
                //登录
                auto &_req = static_cast<RegLoginRequest&>(*_req_ptr);
                int LoginRet = RegLogMan.Login(_req._ip, _req._user_name, _req._password);
                if(LoginRet == LOGIN_USER_NOT_EXIST){
                    meg = "have no the user!";
                    info = "";
                }
                else if(LoginRet == LOGIN_PWD_ERR){
                    meg = "password error!";
                    info = "";
                }
                else if(LoginRet == UNKNOWN_ERR){
                    meg = "Unknown err, contact admin!";
                    info = "";
                }
                else if(LoginRet == LOGIN_SUCCESS){
                    meg = "login success!";
                    info = "";
                }
            }
            default:
                meg = "Bad Request!";
                info = "";
            }
        }
        else
        {
            meg = "Bad Request!";
            info = "";
        }
        // 成功处理的话，加载好并发回_reps
        _reps._info = info;
        _reps._meg = meg;
        std::string ret_info;
        _reps.Serialize(ret_info);
        ret_info = Encode(ret_info);
        write(_socketfd, ret_info.c_str(), ret_info.size());
        close(_socketfd);
    }

    ~Task() {}

private:
    // request _req;
    std::unique_ptr<BaseRequest> _req_ptr;
    response _reps;
    int _socketfd;
    std::string _clientip;
    u_int16_t _clientport;
};