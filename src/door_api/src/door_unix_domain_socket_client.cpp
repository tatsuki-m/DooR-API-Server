#include "door_unix_domain_socket_client.h"

DoorUnixDomainSocketClient::DoorUnixDomainSocketClient(std::string socketName, DoorSocketType type, std::string ack_data) {
    socketName_ = socketName;
    ack_.type = type;
    strcpy(ack_.data, ack_data.c_str());
}

DoorUnixDomainSocketClient::~DoorUnixDomainSocketClient() {
    std::cout << "DoorUnixDomainSocketClient::~" << std::endl;
    closeSocket();
}

bool
DoorUnixDomainSocketClient::run() {
    std::cout << "DoorUnixDomainSocketClient::run" << std::endl;
    create();
    bool is_success = handle();
    return is_success;
}

void
DoorUnixDomainSocketClient::closeSocket() {
    try {
        if(close(server_) == -1) {
            std::cerr << "DoorUnixDomainSocketClient::closeSocket" << std::endl;
            throw;
        }
    } catch(...) {
        unlink(socketName_.c_str());
        close(server_);
    }
}

void
DoorUnixDomainSocketClient::create() {
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

bool
DoorUnixDomainSocketClient::handle() {
    try {
        bool is_sent, is_success;
        is_sent = sendAck();
        if (!is_sent) throw;
        is_success = getResponse();
        if (!is_success) throw;
    } catch(...) {
        unlink(socketName_.c_str());
        close(server_);
    }
    return true;
}

bool
DoorUnixDomainSocketClient::sendAck() {
    std::cout << "UnixDomainSocketLient::sendAck()" << std::endl;
    try {
        int ss;
        if ((ss = send(server_, &ack_, sizeof(ack_), 0)) < 0) {
            std::cerr << "send: " << std::endl;
            return false;
        } else {
            return true;
        }
    } catch(...) {
        unlink(socketName_.c_str());
        close(server_);
        return false;
    }
}

bool
DoorUnixDomainSocketClient::getResponse() {
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
        unlink(socketName_.c_str());
        close(server_);
        return false;
    }
}

