#pragma once
#define protocol_sem '\n'


//操作类型定义
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
#define OP_REGISTER 12     // 注册
#define OP_LOGIN 13        //登录


//权限身份定义
#define ROLE_STU 1         //学生
#define ROLE_TEA 2         //老师
#define ROLE_MAN 3         //管理员

#include <iostream>
#include <cctype>
#include <string>
#include <jsoncpp/json/json.h>
#include "log.hpp"



//解决stoi的异常问题
//-1失败，其它成功
int safeStoi(const string& s){
    if(s.empty()){
        return -1;
    }
    for(auto e : s){
        if(isdigit(e)){
            return -1;
        }
    }
    try{
        int ret = stoi(s);
        return ret;
    }
    catch(const std::invalid_argument& e){
        lg(ERROR, "stoi exception!");
        return -1;
    }
}


//加报头:len+\n+info+\n
std::string Encode(std::string& info){
    std::string package = std::to_string(info.size());
    package += protocol_sem;
    package += info;
    package += protocol_sem;
    return package;
}

//去报头
//len+\n+info+\n : 2\n aa \n
//                              11\n aaaaaaaaaaa \n
//                 0 1 2 3 4    01 2 3 4 ......  
//info->aa
bool Decode(std::string& package, std::string& info){
    std::size_t pos = package.find(protocol_sem);
    if(pos == std::string::npos) return false;
    std::string len_str = package.substr(0, pos);
    int len = safeStoi(len_str);
    if(len <= 0 || len + len_str.size() + 2 > package.size()) return false;
    info = package.substr(pos+1, len);
    package.erase(0, len + len_str.size() + 2);
    return true;
}

class BaseRequest{
public:
    virtual ~BaseRequest(){};
    virtual bool Serialize(std::string &out) = 0;
    virtual bool DeSerialize(const std::string &in) = 0;
    virtual int GetOp() const = 0;
    std::string _op_type;
};

//对信息的增删查改
class StuRequest : public BaseRequest
{
public:
    StuRequest(){}
    StuRequest(std::string op_type, std::string order, std::string name, std::string id, double score)
    :_order(order)
    ,_name(name)
    ,_id(id)
    ,_score(score)
    {
        _op_type = op_type;
    }
    // 序列化
    bool Serialize(std::string &out)
    {
        Json::Value root;
        Json::FastWriter w;
        root["_op_type"] = _op_type;
        root["_name"] = _name;
        root["_id"] = _id;
        root["_order"] = _order;
        root["_score"] = _score;
        out = w.write(root);
        return true;
    }
    // 反序列化
    bool DeSerialize(const std::string &in)
    {
        Json::Value root;
        Json::Reader r;
        r.parse(in, root);
        _op_type = root["_op_type"].asString();
        _name = root["_name"].asString();
        _id = root["_id"].asString();
        _score = root["_score"].asDouble();
        _order = root["_order"].asString();
        return true;
    }
    int GetOp() const{
        return safeStoi(_op_type);
    }
    // virtual ~BaseRequest() = 0;
    // virtual bool Serialize(std::string &out) = 0;
    // virtual bool DeSerialize(const std::string &in) = 0;
    // virtual int GetOp() = 0;
    // std::string _op_type;
    std::string _order;//排序的时候的升降序
    std::string _name;
    std::string _id;
    double _score;
};

class RegLoginRequest : public BaseRequest
{
public:
    RegLoginRequest(){}
    RegLoginRequest(std::string user_name, std::string password, int role, std::string op_type){
        _user_name =user_name;
        _password = password;
        _role = to_string(role);
        _op_type = op_type;
    }
    bool Serialize(std::string &out){
        Json::Value root;
        Json::FastWriter w;
        root["_ip"] = _ip;
        root["_user_name"] = _user_name;
        root["_password"] = _password;
        root["_role"] = _role;
        root["_op_type"] = _op_type;
        out = w.write(root);
        return true;
    }

    bool DeSerialize(const std::string &in){
        Json::Value root;
        Json::Reader r;
        r.parse(in, root);
        _ip = root["_ip"].asString();
        _user_name = root["_user_name"].asString();
        _password = root["_password"].asString();
        _role = root["_role"].asString();
        _op_type = root["_op_type"].asString();
        return true;
    }

    int GetOp() const{
        return safeStoi(_op_type);
    }
    // virtual ~BaseRequest() = 0;
    // virtual bool Serialize(std::string &out) = 0;
    // virtual bool DeSerialize(const std::string &in) = 0;
    // virtual int GetOp() = 0;

    //<ip+用户名， ip+用户名+密码+权限>;
    std::string _ip;
    std::string _user_name;
    std::string _password;
    std::string _role = "0"; 
    //std::string _op_type;
};

class response
{
public:
    response(){}
    response(const std::string info){
        DeSerialize(info);
    }

    response(const response& reps)
    :_info(reps._info)
    ,_meg(reps._meg)
    ,_confirm_code(reps._confirm_code)
    ,_permission(reps._permission)
    {}

    bool Serialize(std::string &out)
    {
        Json::Value root;
        Json::FastWriter w;
        root["_info"] = _info;
        root["_meg"] = _meg;
        root["_confirm_code"] = _confirm_code;
        root["_permission"] = _permission;
        out = w.write(root);
        return true;
    }
    // 反序列化
    bool DeSerialize(const std::string &in)
    {
        Json::Value root;
        Json::Reader r;
        r.parse(in, root);
        _info = root["_info"].asString();
        _meg = root["_meg"].asString();
        _confirm_code = root["_confirm_code"].asInt();
        _permission = root["_permission"].asInt();
        return true;
    }
    std::string _info;//存储查找操作的时候信息
    std::string _meg;//存储确认信息
    int _confirm_code = -1;//登录注册时返回，0失败，1成功
    int _permission = -1;//1学生2老师3管理员
};


