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

class UnixSocket : public ISubject
{

public:
    UnixSocket(std::string socketName);
    UnixSocket(std::string socketName, unsigned int workerID);
    ~UnixSocket();
    void run();

private:
    enum Type {
        SHARED_SOCKET = 0,
        SHARED_MEMORY = 1,
    } type_;

    void create();
    void closeSocket();
    void serve();
    void handle(int);
    void notifyServer(std::string);
    void sendSocketName(int);
    bool getRequest(int, char&);
    int server_;
    unsigned int workerID_;
    unsigned int connectionNum_;
    std::string socketName_;
};


