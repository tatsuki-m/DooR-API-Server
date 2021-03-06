#ifndef SOCKET_CLIENT_H_
#define SOCKET_CLIENT_H_

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>

#include "dpi.h"

class SocketClient {

public:
    SocketClient(std::string);
    SocketClient(std::string, std::string, int);
    ~SocketClient();

    void run();
    void getDpi(Dpi*& dpi);
    void closeSocket();
    void handle();
private:
    void createUnixDomain();
    void createTcp();
    bool sendAck();
    bool getResponse();

    int server_;
    int port_;
    // for mesurement
    static int counter;
    std::string socketName_;
    std::string addr_;
    ConType type_;
    Dpi dpi_;
};

#endif

