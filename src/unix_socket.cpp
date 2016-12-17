#ifndef UNIX_SOCKET_H_
#define UNIX_SOCKET_H_

#include "unix_socket.h"

const char* UnixSocket::socketName_ = "/tmp/unix-socket";
const char* UnixSocket::baseKey_ = "shmKey";

UnixSocket::UnixSocket() {
    std::cout << "UnixSocket" << std::this_thread::get_id() << std::endl;
    //register_handler();
    unlink(socketName_);
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
        std::cout << "socket running" << std::endl;
        if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0)
            handle(client);
    }
    closeSocket();
}

void
UnixSocket::handle(int client) {
    bool success;

    if (getAck(client)) {
        connectionNum_++;
        success = sendResponse(client);
        if (success) {
            notifyServer();
        }
    }
}

bool
UnixSocket::getAck(int client) {
    recv(client, &ack_, sizeof(&ack_), 0);
    printf("return ack_ =%d\n", ack_);

    if (ack_ == 0)
      return true;
    else
      return false;
}

bool
UnixSocket::sendResponse(int client) {
    int cc;
    std::string shmKey = KeyGenerator::createKey((char *)baseKey_, connectionNum_);
    const char *sendBuf = shmKey.c_str();
    std::cout << sendBuf << std::endl;

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
    std::string shmKey = KeyGenerator::createKey((char *)baseKey_, connectionNum_);
    ISubject::notify(shmKey);
}

#endif

