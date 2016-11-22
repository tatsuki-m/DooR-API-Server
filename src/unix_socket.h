#pragma once

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>

#include "observer.h"

class UnixSocket : public ISubject
{

public:
    UnixSocket();
    ~UnixSocket();
    void run();

private:
    void create();
    void closeSocket();
    void serve();
    void handle(int);
    void registerHandler();
    void notifyServer();
    bool getAck(int);
    bool sendResponse(int);
    static void interrupt(int);

    int server_;
    int ack_;
    int containerNum_;
    static const char* socketName_;
};


