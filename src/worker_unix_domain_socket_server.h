//#ifdef WORKER_UNIX_DOMAIN_SOCKET_SERVER_H_
//#define WORKER_UNIX_DOMAIN_SOCKET_SERVER_H_

#include <iostream>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string>
#include <thread>

#include "key_generator.h"
#include "door_unix_domain_socket_client/socket_ack.h"

class WorkerUnixDomainSocketServer
{

public:
    WorkerUnixDomainSocketServer(std::string, unsigned int);
    ~WorkerUnixDomainSocketServer();
    void run();
    void sendDestroy();

private:
    void create();
    void serve();
    void handle(int);
    void sendDoorShmKey(int, SocketAck&);
    bool getRequest(int, SocketAck&);
    void closeSocket();
    int server_;
    unsigned int workerId_;
    unsigned int counter_;
    std::string socketName_;
};

//#endif

