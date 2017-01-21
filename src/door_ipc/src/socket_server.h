#ifndef SOCKET_SERVER_H_
#define SOCKET_SERVER_H_

#include <iostream>
#include <string>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/un.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "dpi.h"
#include "sync_semaphore.h"

class SocketServer
{

public:
    SocketServer(std::string);
    SocketServer(std::string, std::string, int);
    ~SocketServer();
    void run();
private:
    void createUnixDomain();
    void createTcp();
    void serveUnixDomain();
    void serveTcp();
    void closeSocket();
    void handle(int);
    bool getRequest(int, Dpi&);
    void sendDpiData(int, Dpi&);
    void notifyClient();

    int server_;
    int port_;
    std::string socketName_;
    std::string addr_;
    ConType type_;
    SyncSemaphore sem_;
};

#endif

