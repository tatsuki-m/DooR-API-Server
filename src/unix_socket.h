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
    // static void interrupt(int);

    int server_;
    int ack_;
    unsigned int connectionNum_;
    static const char* socketName_;
    static const char* baseKey_;
};


