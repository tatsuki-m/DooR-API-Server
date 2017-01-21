#include "socket_server.h"

SocketServer::SocketServer(std::string socketName) {
    std::string base_dir = "/tmp/unix-socket/";
    socketName_ = base_dir + socketName;
    type_ = UNIX_DOMAIN;
    addr_ = "";
    port_ = 0;
    unlink(socketName_.c_str());
}

SocketServer::SocketServer(std::string socketName, std::string addr, int port) {
    std::string base_dir = "/tmp/unix-socket/";
    socketName_ = base_dir + socketName;
    type_ = TCP;
    addr_ = addr;
    port_ = port;
    unlink(socketName_.c_str());
}

SocketServer::~SocketServer() {
}

void
SocketServer::closeSocket() {
    try {
        if(close(server_) == -1) {
            std::cerr << "SocketServer::closeSocket" << std::endl;
            throw;
        }
        unlink(socketName_.c_str());
        sem_.close();
    } catch(...) {
        unlink(socketName_.c_str());
        close(server_);
        sem_.close();
    }
}

void
SocketServer::run() {
    //std::cout << "SocketClient::run" << std::endl;
    switch (type_) {
        case UNIX_DOMAIN:
            std::cout << "CASE: UNIXDOMAIN" << std::endl;
            createUnixDomain();
            serveUnixDomain();
            break;
        case TCP:
            std::cout << "CASE: TCP" << std::endl;
            createTcp();
            serveTcp();
            break;
        default:
            createUnixDomain();
            serveUnixDomain();
            break;
    }
}

void
SocketServer::createUnixDomain() {
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
            std::cerr << "SocketServer::Create socket: ";
            throw;
        }

        if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
            std::cerr << "SocketServer::Create setsockopt: ";
            throw;
        }

        // call bind to associate the socket with the UNIX file system
        if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "SocketServer::Create bind: ";
            throw;
        }

        // convert the socket listen for incoming connections
        if (listen(server_, 10) < 0) {
            std::cerr << "SocketServer::Create listen: ";
            throw;
        }
    } catch(...) {
        closeSocket();
    }
}

void
SocketServer::createTcp() {
    try {
        struct sockaddr_in server_addr;
        int soval = 1;

        // setup socket address structure
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(addr_.c_str());
        server_addr.sin_port = port_;

        // create socket
        server_ = socket(AF_INET, SOCK_STREAM, 0);
        if (!server_) {
            std::cerr << "SocketServer::Create socket: ";
            throw;
        }

        if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
            std::cerr << "SocketServer::Create setsockopt: ";
            throw;
        }

        // call bind to associate the socket with the UNIX file system
        if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "SocketServer::Create bind: ";
            throw;
        }

        // convert the socket listen for incoming connections
        if (listen(server_, 10) < 0) {
            std::cerr << "SocketServer::Create listen: ";
            throw;
        }
    } catch(...) {
        closeSocket();
    }
}

void
SocketServer::serveUnixDomain() {
    int client;
    int counter = 0;
    struct sockaddr_un client_addr;
    socklen_t clientlen = sizeof(client_addr);
    sem_.post();
    std::cout << "socketUnixDomain running" << std::endl;
    while (counter<MAX_COUNT) {
        try {
            if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0) {
                handle(client);
            } else {
                throw;
            }
        } catch(...) {
            closeSocket();
        }
        counter++;
    }
    closeSocket();
}

void
SocketServer::serveTcp() {
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while (1) {
        std::cout << "socketTcp running" << std::endl;
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
SocketServer::handle(int client) {
    Dpi dpi;
    bool is_success = getRequest(client, dpi);
    if (is_success) {
        sendDpiData(client, dpi);
    }
}

bool
SocketServer::getRequest(int client, Dpi &dpi) {
    //std::cout << "UnixScoket::getRequest: " << std::endl;
    int cc;
    if ((cc=recv(client, &dpi, sizeof(dpi), 0)) > 0) {
        //std::cout << "UnixScoket::getRequest success " << std::endl;
        return true;
    } else {
        //std::cout << "UnixScoket::getRequest fail " << std::endl;
        return false;
    }
}

void
SocketServer::sendDpiData(int client, Dpi &dpi) {
    //std::cout << "SocketServer::sendDpiData" << std::endl;
    int cc;

    // insertData
    for (unsigned int i =0; i < sizeof(dpi.data_); i++) {
        dpi.data_[i] = 'a';
    }

    try {
        if ((cc = send(client, &dpi, sizeof(dpi), 0)) < 0) {
            std::cerr << "UnisDomainSocketServer::sendSocketName";
            throw;
        }
    } catch(...) {
        closeSocket();
    }
    //std::cout << "SocketServer::sendDpiData success" << std::endl;
}

