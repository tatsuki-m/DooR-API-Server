#include <iostream>
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
#include <thread>

#include "i_subject.h"
#include "key_generator.h"
#include "socket_ack.h"

class UnixSocket : public ISubject
{

public:
    UnixSocket();
    UnixSocket(std::string socketName, unsigned int workerID);
    ~UnixSocket();
    void run();

private:
    void create();
    void closeSocket();
    void serve();
    void handle(int);
    void notifyServer(std::string);
    void sendSocketName(int, SocketAck&);
    bool getRequest(int, SocketAck&);
    int server_;
    unsigned int workerID_;
    unsigned int counter_;
    std::string socketName_;
};


