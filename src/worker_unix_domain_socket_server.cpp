#include "worker_unix_domain_socket_server.h"

std::string BASE_SHM_KEY = "ShmKey";

WorkerUnixDomainSocketServer::WorkerUnixDomainSocketServer(std::string socketName, unsigned int workerId) {
    std::cout << "WorkerUnixDomainSocketServer SocketName: " << socketName_ << std::endl;
    socketName_ = socketName;
    workerId_ = workerId;
    counter_ = 0;
    stopLoopFlag = false;
    unlink(socketName_.c_str());
}

WorkerUnixDomainSocketServer::~WorkerUnixDomainSocketServer() {
    std::cout << "WorkerUnixDomainSocketServer:~WorkerUnixDomainSocketServer"  << std::endl;
}

void
WorkerUnixDomainSocketServer::run() {
    create();
    serve();
    closeSocket();
}

void
WorkerUnixDomainSocketServer::closeSocket() {
    std::cout << "WorkerUnixDomainSocketServer::closeSocket()" << std::endl;
    close(sockfd_);
    std::cout << "close success" << std::endl;
    unlink(socketName_.c_str());
    std::cout << "unlink success" << std::endl;
}

void
WorkerUnixDomainSocketServer::create() {
    try {
        struct sockaddr_un server_addr;
        int soval = 1;

        // setup socket address structure
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strncpy(server_addr.sun_path, socketName_.c_str(), sizeof(server_addr.sun_path) -1);

        // create socket
        sockfd_ = socket(AF_UNIX, SOCK_STREAM, 0);
        if (!sockfd_) {
            std::cerr << "WorkerUnixDomainSocketServer::Create socket: ";
            throw;
        }

        if (setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
            std::cerr << "WorkerUnixDomainSocketServer::Create setsockopt: ";
            throw;
        }

        // call bind to associate the socket with the UNIX file system
        if (bind(sockfd_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "WorkerUnixDomainSocketServer::Create bind: ";
            throw;
        }

        // convert the socket listen for incoming connections
        if (listen(sockfd_, 10) < 0) {
            std::cerr << "WorkerUnixDomainSocketServer::Create listen: ";
            throw;
        }
    } catch(...) {
        closeSocket();
    }
}

void
WorkerUnixDomainSocketServer::serve() {
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while (true && !stopLoopFlag) {
        std::cout << "WorkerUnixDomainSocketServer running" << std::endl;
        try {
            std::cout << "accepting...." << std::endl;
            if ((client = accept(sockfd_, (struct sockaddr *)&client_addr, &clientlen)) > 0) {
                fcntl(sockfd_, F_SETFL, O_NONBLOCK);;
                handle(client);
            } else {
                throw;
            }
        } catch(...) {
            closeSocket();
        }
    }
}

void
WorkerUnixDomainSocketServer::handle(int client) {
    bool is_success;
    SocketAck ack;
    if (is_success = getRequest(client, ack)) {
        switch(ack.type) {
            case ASK_SHM:
                counter_++;
                writeShmKey(ack);
                break;
            case STOP_SOCKET_SERVER:
                stopServer();
            default:
                break;
        }
        sendAck(client, ack);
    }
}

bool
WorkerUnixDomainSocketServer::getRequest(int client, SocketAck &ack) {
    std::cout << "UnixScoket::getRequest: " << std::endl;
    int cc;
    if ((cc=recv(client, &ack, sizeof(ack), 0)) > 0) {
        return true;
    } else {
        return false;
    }
}

void
WorkerUnixDomainSocketServer::sendAck(int client, SocketAck &ack) {
    int cc;
    try {
        if ((cc = send(client, &ack, sizeof(ack), 0)) < 0) {
            std::cerr << "WorkerUnixDomainSocketServer::sendSocketName";
            throw;
        } else {
            std::cout << "success" << std::endl;
        }
    } catch(...) {
        closeSocket();
    }
}

void
WorkerUnixDomainSocketServer::writeShmKey(SocketAck &ack) {
    std::cout << "WorkerUnixDomainSocketServer::writeSocketName: " << std::endl;
    std::string doorShmKey = KeyGenerator::createDoorShmKey(BASE_SHM_KEY, workerId_, counter_);
    strcpy(ack.data, doorShmKey.c_str());
}

void
WorkerUnixDomainSocketServer::stopServer() {
    std::cout << "WorkerUnixDomainSocketServer::stopServer()" << std::endl;
    stopLoopFlag = true;
}

