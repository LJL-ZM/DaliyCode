#pragma once

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
#define OP_SAVE_FILE 10    // 保存文件
#define OP_LOAD_FILE 11    // 加载文件

#include <iostream>
#include "Protocol.hpp"
#include "log.hpp"
#include "StudentManager.hpp"

extern Log lg;
extern StudentManager Manager;
class Task
{
private:
public:
    Task(const int &socketfd, const std::string &clientip, u_int16_t clientport)
        : _socketfd(socketfd), _clientip(clientip), _clientport(clientport)
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
                req += request_buf;
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
        if (Decode(req_package, info))
        {
            // 成功解码一条请求
            _req.DeSerialize(info);
            return true;
        }
        else
        {
            // 解码失败
            close(_socketfd);
            lg(WARN, "Decode fail in community with [%s:%d], err str:%s", _clientip.c_str(), _clientport, strerror(errno));
            return false;
        }
    }

    void operator()()
    {
        std::string meg, info;
        if (initTask())
        {
            int op = std::stoi(_req._op_type.c_str());
            Student st(_req._id, _req._name, _req._score);
            switch (op)
            {
            case OP_ADD_STUDENT:
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
            case OP_DEL_STUDENT:
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
            case OP_MOD_STUDENT:
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
            case OP_QUERY_STUDENT:
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
            case OP_GET_ALL:
            {
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
            case OP_SORT_ID:
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
            case OP_STATISTIC:
                int totalCount, excellent, fail;
                float avgScore, maxScore, minScore;
                if (Manager.scoreStatistics(totalCount, avgScore, maxScore, minScore, excellent, fail))
                {
                    // 统计成功，处理统计结果
                    // 先格式化浮点数
                    char avg_buf[32], max_buf[32], min_buf[32];
                    snprintf(avg_buf, sizeof(avg_buf), "%.2f", avgScore);
                    snprintf(max_buf, sizeof(max_buf), "%.2f", maxScore);
                    snprintf(min_buf, sizeof(min_buf), "%.2f", minScore);
                    // 拼接（整数用to_string无问题，浮点数用格式化后的字符串）
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
            case OP_CLEAR_ALL:
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
            default:
                meg = "Bad Request!";
                info = "";
            }
        }
        else{
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
    request _req;
    response _reps;
    int _socketfd;
    std::string _clientip;
    u_int16_t _clientport;
};