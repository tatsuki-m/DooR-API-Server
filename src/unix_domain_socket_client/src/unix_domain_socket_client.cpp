#include "unix_domain_socket_client.h"

UnixDomainSocketClient::UnixDomainSocketClient(std::string socketName, SocketType type) {
    socketName_ = socketName;
    ack_.type = type;
}

UnixDomainSocketClient::UnixDomainSocketClient(std::string socketName, SocketType type, std::string ack_data) {
    socketName_ = socketName;
    ack_.type = type;
    strcpy(ack_.data, ack_data.c_str());
}

UnixDomainSocketClient::~UnixDomainSocketClient() {
    std::cout << "UnixDomainSocketClient::~UnixDomainSocketClient;" << std::endl;
}

void
UnixDomainSocketClient::run() {
    std::cout << "UnixDomainSocketClient::run" << std::endl;
    create();
    handle();
    closeSocket();
}

void
UnixDomainSocketClient::closeSocket() {
    std::cout << "UnixDomainSocketClient::closeSocket" << std::endl;
    try {
        if(close(server_) == -1) {
            std::cerr << "UnixDomainSocketClient::closeSocket" << std::endl;
            throw;
        }
    } catch(...) {
        unlink(socketName_.c_str());
        close(server_);
    }
    close(server_);
}

void
UnixDomainSocketClient::create() {
    try {
        struct sockaddr_un server_addr;

        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strncpy(server_addr.sun_path, socketName_.c_str(), sizeof(server_addr.sun_path) - 1);
        server_ = socket(AF_UNIX, SOCK_STREAM, 0);
        if (!server_) {
            std::cerr << "socket: " << std::endl;
            throw;
        }
        std::cout << "will connect" << std::endl;
        if (connect(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "connect: " << std::endl;
            throw;
        }
    } catch(...) {
        unlink(socketName_.c_str());
        close(server_);
    }
}

void
UnixDomainSocketClient::handle() {
    try {
        bool is_sent, is_success;
        is_sent = sendAck();
        if (!is_sent) throw;
        is_success = getResponse();
        std::cout << "get request: " << is_success << std::endl;
        if (!is_success) throw;
    } catch(...) {
        unlink(socketName_.c_str());
        close(server_);
    }
}

bool
UnixDomainSocketClient::sendAck() {
    std::cout << "UnixDomainSocketClient::sendAck()" << std::endl;
    try {
        int ss;
        if ((ss = send(server_, &ack_, sizeof(ack_), 0)) < 0) {
            std::cerr << "send: " << std::endl;
            return false;
        } else {
            return true;
        }
    } catch(...) {
        std::cout << "error UnixDomainSocketClient::sendAck()" << std::endl;
        unlink(socketName_.c_str());
        close(server_);
        return false;
    }
}

bool
UnixDomainSocketClient::getResponse() {
    std::cout << "UnixDomainSocketClient::getResponse()" << std::endl;
    try {
        int gs;

        std::cout << "waiting response" << std::endl;
        if ((gs = recv(server_, &ack_, sizeof(ack_), 0)) < 0 ) {
            std::cerr << "recv";
            return false;
        } else {
            std::cout << "success: " << ack_.data << std::endl;
            return true;
        }
    } catch(...) {
        std::cout << "error UnixDomainSocketClient::getResponse()" << std::endl;
        unlink(socketName_.c_str());
        close(server_);
        return false;
    }
}

std::string
UnixDomainSocketClient::getRecievedData() {
    std::string data = ack_.data;
    return data;
}

bool
UnixDomainSocketClient::hasResponse() {
    return true;
}

