#pragma once
#define SIZE 1024
#define filename "./log/log"

#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

//错误类型
enum ERR{
    FIFO_CREAT_ERR = 1,
    FIFO_DESTORY_ERR,
    FIFO_OPEN_ERR,
    FIFO_READ_ERR,
    FIFO_WRITE_ERR,
    FFLUSH_ERR,
    KEY_GET_ERR,
    SHM_CREAT_ERR,
    SHM_ATTACH_ERR
};
//日志等级
enum level{
    INFO = 1,
    DEBUG,
    WARN,
    ERROR,
    FATAL
};

//打印方式
enum Print_mode{
    SCREEN = 1,
    ONE_FILE,
    CLASS_FILE
};

class Log{
private:
    string Level_To_String(int level){
        switch(level){
            case INFO:
                return "INFO";
            case DEBUG:
                return "DEBUG";
            case WARN:
                return "WARN";
            case ERROR:
                return "ERROR";
            case FATAL:
                return "FATAL";
        }
        return "warn";
    }
    void Print(int level, string message){
        switch(_Print){
            case SCREEN:
                printf("%s\n", message.c_str());
                break;
            case ONE_FILE:
                one_file(filename, message);
                break;
            case CLASS_FILE:
                class_file(level, message);
                break;

        }
    }
    void one_file(const char* path, string message){
        int fd = open(path, O_RDONLY | O_WRONLY | O_CREAT);   
        if(fd < 0){
            perror("log---open");
            exit(0);
        } 
        message += '\n';
        write(fd, message.c_str(), message.size());
    }
    void class_file(int level, string message){
        string path = filename;
        path += '.';
        path += Level_To_String(level);
        one_file(path.c_str(), message);
    }
public:
    Log(int Print = SCREEN)
    :_Print(Print){}

    void operator()(int level, const char* format, ...){
        //左半边，内置部分
        char left_message[SIZE] = "";
        time_t t = time(NULL);
        struct tm* st = localtime(&t);
        snprintf(left_message, sizeof(left_message), "[%s][%dy%dm%dd %d:%d:%d]", Level_To_String(level).c_str(), st->tm_year + 1900,\
        st->tm_mon + 1, st->tm_mday, st->tm_hour, st->tm_min, st->tm_sec);
        //自定义部分
        char right_message[SIZE] = "";
        va_list v;
        va_start(v, format);
        vsnprintf(right_message, sizeof(right_message), format, v);
        //拼接
        string s_l(left_message), s_r(right_message);
        string message = s_l + s_r;
        Print(level, message);
    } 
private:
    int _Print;
}lg;