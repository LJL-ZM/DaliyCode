#pragma once
#define protocol_sem '\n'

#define OP_ADD_STUDENT 1  
#define OP_DEL_STUDENT 2  
#define OP_MOD_STUDENT 3   
#define OP_QUERY_STUDENT 4  
#define OP_GET_ALL 5       
#define OP_SORT_SCORE 6    
#define OP_SORT_ID 7       
#define OP_STATISTIC 8     
#define OP_CLEAR_ALL 9     
#define OP_SAVE_FILE 10    
#define OP_LOAD_FILE 11    
#define OP_REGISTER 12     
#define OP_LOGIN 13        

#define ROLE_STU 1         
#define ROLE_TEA 2         
#define ROLE_MAN 3         

#include <iostream>
#include <cctype>
#include <string>
#include "json.h" // 替换为单头文件

using json = nlohmann::json;

int safeStoi(const std::string& s) {
    if (s.empty()) {
        return -1;
    }
    for (auto e : s) {
        if (!isdigit(e)) {
            return -1;
        }
    }
    try {
        int ret = std::stoi(s);
        return ret;
    }
    catch (const std::invalid_argument& e) {
        printf("stoi exception!\n");
        return -1;
    }
}

std::string Encode(std::string& info) {
    std::string package = std::to_string(info.size());
    package += protocol_sem;
    package += info;
    package += protocol_sem;
    return package;
}

bool Decode(std::string& package, std::string& info) {
    std::size_t pos = package.find(protocol_sem);
    if (pos == std::string::npos) return false;
    std::string len_str = package.substr(0, pos);
    int len = safeStoi(len_str);
    if (len <= 0 || len + len_str.size() + 2 > package.size()) return false;
    info = package.substr(pos + 1, len);
    package.erase(0, len + len_str.size() + 2);
    return true;
}

class BaseRequest {
public:
    virtual ~BaseRequest() {};
    virtual bool Serialize(std::string& out) = 0;
    virtual bool DeSerialize(const std::string& in) = 0;
    virtual int GetOp() const = 0;
    std::string _op_type;
};

class StuRequest : public BaseRequest
{
public:
    StuRequest() {}
    StuRequest(std::string op_type, std::string order, std::string name, std::string id, double score)
        :_order(order)
        , _name(name)
        , _id(id)
        , _score(score)
    {
        _op_type = op_type;
    }

    bool Serialize(std::string& out)
    {
        json j;
        j["_op_type"] = _op_type;
        j["_name"] = _name;
        j["_id"] = _id;
        j["_order"] = _order;
        j["_score"] = _score;
        out = j.dump();
        return true;
    }

    bool DeSerialize(const std::string& in)
    {
        if (in.empty()) return false;
        try {
            json j = json::parse(in);
            _op_type = j["_op_type"].get<std::string>();
            _name = j["_name"].get<std::string>();
            _id = j["_id"].get<std::string>();
            _score = j["_score"].get<double>();
            _order = j["_order"].get<std::string>();
            return true;
        }
        catch (...) {
            return false;
        }
    }

    int GetOp() const {
        return safeStoi(_op_type);
    }
    std::string _order;
    std::string _name;
    std::string _id;
    double _score;
};

class RegLoginRequest : public BaseRequest
{
public:
    RegLoginRequest() {}
    RegLoginRequest(std::string user_name, std::string password, int role, std::string op_type) {
        _user_name = user_name;
        _password = password;
        _role = std::to_string(role);
        _op_type = op_type;
    }

    bool Serialize(std::string& out) {
        json j;
        j["_ip"] = _ip;
        j["_user_name"] = _user_name;
        j["_password"] = _password;
        j["_role"] = _role;
        j["_op_type"] = _op_type;
        out = j.dump();
        return true;
    }

    bool DeSerialize(const std::string& in) {
        if (in.empty()) return false;
        try {
            json j = json::parse(in);
            _ip = j["_ip"].get<std::string>();
            _user_name = j["_user_name"].get<std::string>();
            _password = j["_password"].get<std::string>();
            _role = j["_role"].get<std::string>();
            _op_type = j["_op_type"].get<std::string>();
            return true;
        }
        catch (...) {
            return false;
        }
    }

    int GetOp() const {
        return safeStoi(_op_type);
    }
    std::string _ip;
    std::string _user_name;
    std::string _password;
    std::string _role = "0";
};

class response
{
public:
    response() {}
    response(const std::string info) {
        DeSerialize(info);
    }

    response(const response& reps)
        :_info(reps._info)
        , _meg(reps._meg)
        , _confirm_code(reps._confirm_code)
        , _permission(reps._permission)
    {}

    bool Serialize(std::string& out)
    {
        json j;
        j["_info"] = _info;
        j["_meg"] = _meg;
        j["_confirm_code"] = _confirm_code;
        j["_permission"] = _permission;
        out = j.dump();
        return true;
    }

    bool DeSerialize(const std::string& in)
    {
        if (in.empty()) return false;
        try {
            json j = json::parse(in);
            _info = j["_info"].get<std::string>();
            _meg = j["_meg"].get<std::string>();
            _confirm_code = j["_confirm_code"].get<int>();
            _permission = j["_permission"].get<int>();
            return true;
        }
        catch (...) {
            return false;
        }
    }
    std::string _info;
    std::string _meg;
    int _confirm_code = -1;
    int _permission = -1;
};