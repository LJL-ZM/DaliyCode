#pragma once

#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <cstring>
#include <sys/stat.h>
#include <errno.h>
#include "log.hpp"
class Daemon
{
private:
    Daemon(int op = 0)
        : _op(op)
    {
    }
    Daemon(const Daemon &) = delete;
    Daemon operator=(const Daemon &) = delete;

public:
    static Daemon &getDaemon()
    {
        return _daemon;
    }
    void Init()
    {
        signal(SIGHUP, SIG_IGN);
        signal(SIGPIPE, SIG_IGN);
        signal(SIGCHLD, SIG_IGN);
        if (fork() > 0)
        {
            exit(0);
        }
        setsid();
        int dev_null = open("/dev/null", O_RDWR);
        if (dev_null < 0)
        {
            lg(ERROR, "daemon err : %s", strerror(errno));
        }
        dup2(dev_null, 0);
        dup2(dev_null, 1);
        dup2(dev_null, 2);
        close(dev_null);
        if (_op && chdir("/") != -1)
        {
            lg(ERROR, "chdir err : %s", strerror(errno));
        }
    }

private:
    static Daemon _daemon;
    int _op = 0;
};
Daemon Daemon::_daemon;