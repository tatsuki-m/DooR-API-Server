//#ifdef UNIX_DOMAIN_SOCKET_SERVER_H_
//#define UNIX_DOMAIN_SOCKET_SERVER_H_

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

#include "i_subject.h"
#include "key_generator.h"
#include "door_unix_domain_socket_client/socket_ack.h"

class UnixDomainSocketServer : public ISubject
{

public:
    UnixDomainSocketServer(std::string);
    ~UnixDomainSocketServer();
    void run();
private:
    void create();
    void serve();
    void closeSocket();
    void handle(int);
    void sendSocketName(int, SocketAck&);
    bool getRequest(int, SocketAck&);
    void notifyCreate(std::string);
    bool notifyDestroy(unsigned int);
    int server_;
    unsigned int counter_;
    std::string socketName_;
};

//#endif

