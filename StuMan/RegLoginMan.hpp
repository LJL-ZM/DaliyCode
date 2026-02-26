#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include "log.hpp"

const std::string UserData_FILE = "./store/userdata.dat"; 

struct UserData{
    char _user_name[64];
    char _ip[32];
    char _password[64];
    char _role[16];

    // 初始化用户数据
    UserData(const std::string& username = "", 
             const std::string& ip = "", 
             const std::string& password = "", 
             const std::string& role = "") {
        memset(this, 0, sizeof(UserData));
        strncpy(_user_name, username.c_str(), sizeof(_user_name)-1);
        strncpy(_ip, ip.c_str(), sizeof(_ip)-1);
        strncpy(_password, password.c_str(), sizeof(_password)-1);
        strncpy(_role, role.c_str(), sizeof(_role)-1);
    }
};

enum {
    READ_FROM_FILE_ERR = 1,
    LOCK_INIT_ERR,
    REG_SUCCESS = 0,
    REG_EXIST,
    REG_FILE_ERR,
    LOGIN_SUCCESS,
    LOGIN_USER_NOT_EXIST,
    LOGIN_PWD_ERR,
    LOGIN_FILE_ERR,
    UNKNOWN_ERR
};

class RegLoginMan{
private:
    // 生成用户唯一键
    std::string genKey(const std::string& ip, const std::string& username) {
        return ip + "_" + username;
    }

    // 保存用户数据到文件
    bool saveToUserDataFile(const std::string& store_filename = UserData_FILE) {
        FILE* fp = fopen(store_filename.c_str(), "wb");
        if (fp == nullptr) {
            lg(ERROR, "open file [%s] fail for write, err:%s", store_filename.c_str(), strerror(errno));
            return false;
        }
        size_t map_size = _userInfo.size();
        size_t write_cnt = fwrite(&map_size, sizeof(map_size), 1, fp);
        if (write_cnt != 1) {
            lg(ERROR, "write map size fail");
            fclose(fp);
            return false;
        }
        for (const auto& pair : _userInfo) {
            size_t key_len = pair.first.size();
            fwrite(&key_len, sizeof(key_len), 1, fp);
            fwrite(pair.first.c_str(), 1, key_len, fp);
            fwrite(&pair.second, sizeof(UserData), 1, fp);
        }
        fflush(fp);
        fclose(fp);
        lg(INFO, "save %lu users success", map_size);
        return true;
    }

    // 从文件加载用户数据
    bool readFromUserDataFile(const std::string& store_filename = UserData_FILE) {
        if (access(store_filename.c_str(), F_OK) != 0) {
            lg(WARN, "file not exist, create new");
            return saveToUserDataFile(store_filename);
        }
        FILE* fp = fopen(store_filename.c_str(), "rb");
        if (fp == nullptr) {
            lg(FATAL, "open file fail for read");
            return false;
        }
        size_t map_size = 0;
        fread(&map_size, sizeof(map_size), 1, fp);
        if (map_size > 10000) {
            lg(FATAL, "invalid map size:%lu", map_size);
            fclose(fp);
            return false;
        }
        _userInfo.clear();
        for (size_t i = 0; i < map_size; ++i) {
            size_t key_len = 0;
            fread(&key_len, sizeof(key_len), 1, fp);
            char key_buf[256] = {0};
            fread(key_buf, 1, key_len, fp);
            std::string key(key_buf, key_len);
            UserData ud;
            fread(&ud, sizeof(UserData), 1, fp);
            _userInfo[key] = ud;
        }
        fclose(fp);
        lg(INFO, "load %lu users success", _userInfo.size());
        return true;
    }

    // 加锁
    bool Lock() {
        int ret = pthread_mutex_lock(&_mutex);
        if (ret != 0) {
            lg(FATAL, "lock fail");
            exit(LOCK_INIT_ERR);
        }
        return true;
    }

    // 解锁
    bool Unlock() {
        int ret = pthread_mutex_unlock(&_mutex);
        if (ret != 0) {
            lg(FATAL, "unlock fail");
            exit(LOCK_INIT_ERR);
        }
        return true;
    }

    // 初始化
    RegLoginMan()
    :_is_init(false) {}

    RegLoginMan(const RegLoginMan&) = delete;
    RegLoginMan& operator=(const RegLoginMan&) = delete;
public:
    static RegLoginMan& getInstance(){
        if(_ptr == nullptr){
            pthread_mutex_lock(&_static_creat_mutex);
            if(_ptr == nullptr){
                _ptr = new RegLoginMan();
            }
            pthread_mutex_unlock(&_static_creat_mutex);
        }
        return *_ptr;
    }
    void Init(){
        if(_is_init){
            return;
        }
        pthread_mutex_lock(&_static_creat_mutex);
        if(_is_init){
            pthread_mutex_unlock(&_static_creat_mutex);
            return;
        }
        int ret = pthread_mutex_init(&_mutex, nullptr);
        if (ret != 0) {
            lg(FATAL, "mutex init fail");
            exit(LOCK_INIT_ERR);
        }
        if (!readFromUserDataFile()) {
            lg(FATAL, "read file fail");
            exit(READ_FROM_FILE_ERR);
        }
        _is_init = true;
        pthread_mutex_unlock(&_static_creat_mutex);
    }
    const int getPermission(const std::string& ip, const string& user_name) {
        Lock();
        const std::string& key = genKey(ip, user_name);
        Unlock();
        return std::stoi(_userInfo[key]._role);
    }
    // 注册
    int Register(const std::string& ip, 
                 const std::string& username, 
                 const std::string& password, 
                 const std::string& role) {
        Lock();
        int ret = UNKNOWN_ERR;
        std::string key = genKey(ip, username);
        if (_userInfo.find(key) == _userInfo.end()) {
            _userInfo[key] = UserData(username, ip, password, role);
            if (saveToUserDataFile()) {
                lg(INFO, "register success: %s@%s", username.c_str(), ip.c_str());
                ret = REG_SUCCESS;
            } else {
                _userInfo.erase(key);
                lg(ERROR, "register fail: save file error");
                ret = REG_FILE_ERR;
            }
        } else {
            lg(WARN, "register fail: %s@%s already exist", username.c_str(), ip.c_str());
            ret = REG_EXIST;
        }
        Unlock();
        return ret;
    }

    // 登录
    int Login(const std::string& ip, 
              const std::string& username, 
              const std::string& password) {
        Lock();
        int ret = UNKNOWN_ERR;
        std::string key = genKey(ip, username);
        if (_userInfo.find(key) == _userInfo.end()) {
            lg(WARN, "login fail: %s@%s not exist", username.c_str(), ip.c_str());
            ret = LOGIN_USER_NOT_EXIST;
        } else {
            std::string stored_pwd(_userInfo[key]._password);
            if (stored_pwd != password) {
                lg(WARN, "login fail: password error");
                ret = LOGIN_PWD_ERR;
            } else {
                lg(INFO, "login success: %s@%s", username.c_str(), ip.c_str());
                ret = LOGIN_SUCCESS;
            }
        }
        Unlock();
        return ret;
    }

    // 析构
    ~RegLoginMan() {
        saveToUserDataFile();
        pthread_mutex_destroy(&_mutex);
    }

private:
    std::unordered_map<std::string, UserData> _userInfo;//ip+用户名：ip、用户名、密码、权限
    pthread_mutex_t _mutex;
    bool _is_init;

    static pthread_mutex_t _static_creat_mutex;
    static RegLoginMan* _ptr;
};

pthread_mutex_t RegLoginMan::_static_creat_mutex = PTHREAD_MUTEX_INITIALIZER;
RegLoginMan* RegLoginMan::_ptr = nullptr;

#define RegLogMan RegLoginMan::getInstance()