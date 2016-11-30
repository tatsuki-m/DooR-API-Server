#ifndef UNIX_SOCKET_H_
#define UNIX_SOCKET_H_

#include <iostream>
#include "unix_socket.h"


UnixSocket::UnixSocket(std::string socketName) {

    //register_handler();
    unlink(socketName.c_str());
    socketName_ = socketName.c_str();
    ack_ = 1;
    connectionNum_ = 0;
}

UnixSocket::~UnixSocket() {
}

/*
void
register_handler() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = interrupt;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}
*/

void
UnixSocket::run() {
    create();
    serve();
}

void
UnixSocket::create() {
    struct sockaddr_un server_addr;
    int soval = 1;

    // setup socket address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, socketName_, sizeof(server_addr.sun_path) -1);

    // create socket
    server_ = socket(PF_UNIX, SOCK_STREAM, 0);
    if (!server_) {
        perror("socket");
        exit(-1);
    }

    if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
        perror("setsockopt");
        exit(-1);
    }

    // call bind to associate the socket with the UNIX file system
    if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

    // convert the socket listen for incoming connections
    if (listen(server_, SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);
    }
}

void
UnixSocket::serve() {
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while (1) {
        if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0)
            handle(client);
    }
    closeSocket();
}

void
UnixSocket::handle(int client) {
    bool success;
    if (getAck(client)) {
        success = sendResponse(client);
        if (success) {
            connectionNum_++;
            notifyServer();
        }
    }
}

bool
UnixSocket::getAck(int client) {
    recv(client, &ack_, sizeof(&ack_), 0);
    printf("return ack_ =%d\n", ack_);

    if (ack_ == 1)
      return true;
    else
      return false;
}

bool
UnixSocket::sendResponse(int client) {
    int cc;
    std::string shmKey = getShmKey();
    const char *sendBuf = shmKey.c_str();

    if ((cc = send(client, sendBuf, sizeof(sendBuf), 0)) < 0) {
        perror("send");
        return false;
    } else {
        return true;
    }
}

void
UnixSocket::closeSocket() {
    unlink(socketName_);
}

void
UnixSocket::notifyServer() {
    ISubject::notify(getShmKey());
}

std::string
UnixSocket::getShmKey() {
    std::string shmKey = "/tmp/unix-socket" + std::to_string(connectionNum_);
    return shmKey;
}

#endif

