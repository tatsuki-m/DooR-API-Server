#ifndef DOOR_UNIX_DOMAIN_SOCKET_CLIENT_H_
#define DOOR_UNIX_DOMAIN_SOCKET_CLIENT_H_

#pragma once

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

#include "door_socket.h"

class DoorUnixDomainSocketClient {

public:
    DoorUnixDomainSocketClient(std::string, DoorSocketType, std::string);
    ~DoorUnixDomainSocketClient();

    bool run();
    std::string getRecievedData();

private:
    void create();
    bool handle();
    bool sendAck();
    bool getResponse();
    void closeSocket();

    struct DoorSocket ack_;
    int server_;
    std::string socketName_;
};

#endif

