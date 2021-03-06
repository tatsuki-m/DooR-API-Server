#include "unix_domain_socket_server.h"

UnixDomainSocketServer::UnixDomainSocketServer(std::string socketName) {
    socketName_ = socketName;
    counter_ = 0;
    unlink(socketName_.c_str());
}

UnixDomainSocketServer::~UnixDomainSocketServer() {
}

void
UnixDomainSocketServer::run() {
    create();
    serve();
    closeSocket();
}

void
UnixDomainSocketServer::closeSocket() {
    std::cout << "UnixDomainSocketServer::closeSocket()" << std::endl;
    std::cerr << "Going to sleep.." << std::endl;
    unlink(socketName_.c_str());
    exit(2);
}

void
UnixDomainSocketServer::create() {
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
            std::cerr << "UnixDomainSocketServer::Create socket: ";
            throw;
        }

        if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
            std::cerr << "UnixDomainSocketServer::Create setsockopt: ";
            throw;
        }

        // call bind to associate the socket with the UNIX file system
        if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "UnixDomainSocketServer::Create bind: ";
            throw;
        }

        // convert the socket listen for incoming connections
        if (listen(server_, 10) < 0) {
            std::cerr << "UnixDomainSocketServer::Create listen: ";
            throw;
        }
    } catch(...) {
        closeSocket();
    }
}

void
UnixDomainSocketServer::serve() {
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while (1) {
        std::cout << "UnixDomainSocketServer running" << std::endl;
        try {
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
UnixDomainSocketServer::handle(int client) {
    bool is_success;
    SocketAck ack;  /* ack.request a: ask socketName */
    if (is_success = getRequest(client, ack)) {
        switch(ack.type) {
            case ASK_SOCKET:
                counter_++;
                sendSocketName(client, ack);
                break;
            default:
                break;
        }
    }
}

bool
UnixDomainSocketServer::getRequest(int client, SocketAck &ack) {
    std::cout << "UnixScoket::getRequest: " << std::endl;
    int cc;
    if ((cc=recv(client, &ack, sizeof(ack), 0)) > 0) {
        return true;
    } else {
        return false;
    }
}

void
UnixDomainSocketServer::sendSocketName(int client, SocketAck &ack) {
    std::cout << "UnixDomainSocketServer::sendSocketName: " << std::endl;
    int cc;
    std::string socketName = KeyGenerator::createSocketName(socketName_, counter_);
    strcpy(ack.data, socketName.c_str());
    std::cout << "socket Name: ack.data =  " << ack.data << std::endl;
    std::cout << "socket Name: socketName = " << socketName << std::endl;
    std::cout << "socket Name: socketName.c_str() = " << socketName.c_str() << std::endl;

    try {
        if ((cc = send(client, &ack, sizeof(ack), 0)) < 0) {
            std::cerr << "UnixDomainSocketServer::sendSocketName";
            throw;
        } else {
            notifyCreate(socketName);
            //notifyDestroy(1);
        }
    } catch(...) {
        closeSocket();
    }

}

void
UnixDomainSocketServer::notifyCreate(std::string socketName) {
    std::cout << "UnixDomainSocketServer::notifyCreate()" << std::endl;
    ISubject::notifyCreate(socketName);
}

bool
UnixDomainSocketServer::notifyDestroy(unsigned int workerId) {
    std::cout << "UnixDomainSocketServer::notifyDestroy()" << std::endl;
    ISubject::notifyDestroy(workerId);
}

