#include "worker_unix_domain_socket_server.h"

std::string BASE_SHM_KEY = "ShmKey";

WorkerUnixDomainSocketServer::WorkerUnixDomainSocketServer(std::string socketName, unsigned int workerId) {
    std::cout << "WorkerUnixDomainSocketServer: " << std::this_thread::get_id() << std::endl;
    std::cout << "WorkerUnixDomainSocketServer SocketName: " << socketName_ << std::endl;
    socketName_ = socketName;
    workerId_ = workerId;
    counter_ = 0;
    unlink(socketName_.c_str());
}

WorkerUnixDomainSocketServer::~WorkerUnixDomainSocketServer() {
    closeSocket();
}

void
WorkerUnixDomainSocketServer::run() {
    create();
    serve();
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
        server_ = socket(AF_UNIX, SOCK_STREAM, 0);
        if (!server_) {
            std::cerr << "WorkerUnixDomainSocketServer::Create socket: ";
            throw;
        }

        if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
            std::cerr << "WorkerUnixDomainSocketServer::Create setsockopt: ";
            throw;
        }

        // call bind to associate the socket with the UNIX file system
        if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "WorkerUnixDomainSocketServer::Create bind: ";
            throw;
        }

        // convert the socket listen for incoming connections
        if (listen(server_, 10) < 0) {
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

    while (true) {
        std::cout << "WorkerUnixDomainSocketServer running" << std::endl;
        try {
            std::cout << "accepting...." << std::endl;
            if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0) {
                handle(client);
            } else {
                throw;
            }
        } catch(...) {
            closeSocket();
        }
    }
    closeSocket();
}

void
WorkerUnixDomainSocketServer::handle(int client) {
    bool is_success;
    SocketAck ack;
    if (is_success = getRequest(client, ack)) {
        switch(ack.type) {
            case ASK_SHM:
                counter_++;
                sendDoorShmKey(client, ack);
                break;
            default:
                break;
        }
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
WorkerUnixDomainSocketServer::sendDoorShmKey(int client, SocketAck &ack) {
    std::cout << "WorkerUnixDomainSocketServer::sendSocketName: " << std::endl;
    int cc;
    std::string doorShmKey = KeyGenerator::createDoorShmKey(BASE_SHM_KEY, workerId_, counter_);
    strcpy(ack.data, doorShmKey.c_str());

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
WorkerUnixDomainSocketServer::sendDestroy() {
    std::cout << "WorkerUnixDomainSocketServer::sendDestroy()" << std::endl;
    closeSocket();
}

void
WorkerUnixDomainSocketServer::closeSocket() {
    std::cout << "WorkerUnixDomainSocketServer::closeSocket()" << std::endl;
    close(server_);
    unlink(socketName_.c_str());
}

