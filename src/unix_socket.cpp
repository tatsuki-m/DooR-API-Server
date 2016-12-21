#include "unix_socket.h"

std::string BASE_SOCKET_NAME = "/tmp/unix-socket";

// default  use for SHARED_SOCKET
UnixSocket::UnixSocket() {
    std::cout << "UnixSocket: " << std::this_thread::get_id() << std::endl;
    socketName_ = BASE_SOCKET_NAME;
    counter_ = 0;
    unlink(socketName_.c_str());
}

UnixSocket::~UnixSocket() {
    closeSocket();
}

void
UnixSocket::run() {
    create();
    serve();
}

void
UnixSocket::create() {
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
            std::cerr << "UnixSocket::Create socket: ";
            throw;
        }

        if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
            std::cerr << "UnixSocket::Create setsockopt: ";
            throw;
        }

        // call bind to associate the socket with the UNIX file system
        if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "UnixSocket::Create bind: ";
            throw;
        }

        // convert the socket listen for incoming connections
        if (listen(server_, 10) < 0) {
            std::cerr << "UnixSocket::Create listen: ";
            throw;
        }
    } catch(...) {
        closeSocket();
    }
}

void
UnixSocket::serve() {
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while (1) {
        std::cout << "socket running" << std::endl;
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
UnixSocket::handle(int client) {
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
UnixSocket::getRequest(int client, SocketAck &ack) {
    std::cout << "UnixScoket::getRequest: " << std::endl;
    int cc;
    if ((cc=recv(client, &ack, sizeof(ack), 0)) > 0) {
        return true;
    } else {
        return false;
    }
}

void
UnixSocket::sendSocketName(int client, SocketAck &ack) {
    std::cout << "UnixSocket::sendSocketName: " << std::endl;
    int cc;
    std::string socketName = KeyGenerator::createSocketName(BASE_SOCKET_NAME, counter_);
    strcpy(ack.data, socketName.c_str());

    try {
        if ((cc = send(client, &ack, sizeof(ack), 0)) < 0) {
            std::cerr << "UnixSocket::sendSocketName";
            throw;
        } else {
            notifyServer(socketName);
        }
    } catch(...) {
        closeSocket();
    }

}

void
UnixSocket::notifyServer(std::string socketName) {
    std::cout << "UnixSocket::notifyServer()" << std::endl;
    ISubject::notify(socketName);
}

void
UnixSocket::closeSocket() {
    std::cout << "UnixSocket::closeSocket()" << std::endl;
    unlink(socketName_.c_str());
}

