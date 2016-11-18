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

class UnixServer {

public:
    UnixServer();
    ~UnixServer();
    void run();

private:
    void create();
    void close_socket();
    void serve();
    void handle(int);
    void register_handler();
    bool get_ack(int);
    bool send_response(int);
    static void interrupt(int);

    int server_;
    int ack_;
    int* container_num_;
    static const char* socket_name_;
};


