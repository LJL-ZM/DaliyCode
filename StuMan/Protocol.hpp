#pragma once
#define protocol_sem '\n'

#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

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
    std::size_t len = std::stoi(len_str);
    if(len + len_str.size() + 2 > package.size()) return false;
    info = package.substr(pos+1, len);
    package.erase(0, len + len_str.size() + 2);
    return true;
}

class request
{
public:
    // 序列化
    bool Serialize(std::string &out)
    {
        Json::Value root;
        Json::FastWriter w;
        root["_op_type"] = _op_type;
        root["_name"] = _name;
        root["_id"] = _id;
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
    }

private:
    std::string _op_type;
    std::string _name;
    std::string _id;
    double _score;
};

class response
{
public:
    bool Serialize(std::string &out)
    {
        Json::Value root;
        Json::FastWriter w;
        root["_info"] = _info;
        root["_meg"] = _meg;
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
    }

private:
    std::string _info;//存储查找操作的时候信息
    std::string _meg;//存储确认信息
};