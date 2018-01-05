#ifndef UNIX_DOMAIN_SOCKET_CLIENT_H_
#define UNIX_DOMAIN_SOCKET_CLIENT_H_

//#pragma once

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>

#include "socket_ack.h"

class UnixDomainSocketClient {

public:
    UnixDomainSocketClient(std::string, SocketType);
    UnixDomainSocketClient(std::string, SocketType, std::string);
    ~UnixDomainSocketClient();

    void run();
    std::string getRecievedData();
    bool hasResponse();

private:
    void create();
    void handle();
    bool sendAck();
    bool getResponse();
    void closeSocket();
    std::string getSocketName();
    std::string getShmKey();

    struct SocketAck ack_;
    int server_;
    std::string socketName_;
};

#endif

