#pragma once

#include <iostream>
#include <pthread.h>
#include <queue>
#include <vector>
#include <string>

struct MyThread
{
    std::string _name;
    pthread_t _tid;
};

template <class T>
class ThreadPoll
{
private:
    static const size_t n = 5;
    void Lock()
    {
        pthread_mutex_lock(&_mutex);
    }
    void Unlock()
    {
        pthread_mutex_unlock(&_mutex);
    }
    T pop()
    {
        T ret = _q.front();
        _q.pop();
        return ret;
    }
    void signal()
    {
        pthread_cond_signal(&_cond);
    }
    void wait()
    {
        pthread_cond_wait(&_cond, &_mutex);
    }
    std::string Get_name(pthread_t tid){
        std::string ret;
        for(auto e : _thread_poll){
            if(e._tid == tid){
                ret = e._name;
            }
        }
        return ret;
    }
    static void* ThreadRoutine(void *arg)
    {
        ThreadPoll<T> *self = (ThreadPoll<T> *)arg;
        while (true)
        {
            self->Lock();
            while ((self->_q).empty())
            {
                self->wait();
            }
            T task = self->pop();
            self->Unlock();
            task();
            pthread_mutex_lock(&(self->_screen_mutex));
            printf("i am %s,i consum a task : %s\n", self->Get_name(pthread_self()).c_str(), (task.Get_ret()).c_str());
            pthread_mutex_unlock(&(self->_screen_mutex));
        }
    }

public:
    ThreadPoll(size_t num = n)
        : _num(num)
        ,_thread_poll(num)
    {
        pthread_mutex_init(&_mutex, nullptr);
        pthread_mutex_init(&_screen_mutex, nullptr);
        pthread_cond_init(&_cond, nullptr);
    }
    void push(const T &in)
    {
        Lock();
        _q.push(in);
        printf("push a task : %s\n", (in.Get_task()).c_str());
        Unlock();
        signal();
    }
    void run()
    {
        for (int i = 0; i < _num; i++)
        {
            _thread_poll[i]._name = std::string("product") + std::string("-") + std::to_string(i);
            pthread_create(&(_thread_poll[i]._tid), nullptr, ThreadRoutine, this);
        }
    }
    ~ThreadPoll()
    {
        for (auto e : _thread_poll)
        {
            pthread_join((e._tid), nullptr);
        }
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_cond);
    }

private:
    std::vector<MyThread> _thread_poll;
    std::queue<T> _q;
    size_t _num;
    pthread_mutex_t _mutex;
    pthread_cond_t _cond;
    pthread_mutex_t _screen_mutex;
};
