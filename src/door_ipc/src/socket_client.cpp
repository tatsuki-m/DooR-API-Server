#include "socket_client.h"

std::string BASE_SOCKET_DIR = "/tmp/unix-socket/";

SocketClient::SocketClient(std::string socketName) {
    socketName_ = BASE_SOCKET_DIR + socketName;
    type_ = UNIX_DOMAIN;
    addr_ = "";
    port_ = 0;
}

SocketClient::SocketClient(std::string socketName, std::string addr, int port) {
    socketName_ = BASE_SOCKET_DIR + socketName;
    type_ = TCP;
    addr_ = addr;
    port_ = port;
}

SocketClient::~SocketClient() {
}

void
SocketClient::closeSocket() {
    try {
        if(close(server_) == -1) {
            std::cerr << "SocketClient::closeSocket: ";
            throw;
        }
    } catch(...) {
        close(server_);
    }
}

void
SocketClient::run() {
    std::cout << "SocketClient::run" << std::endl;
    switch (type_) {
        case UNIX_DOMAIN:
            std::cout << "CASE: UNIXDOMAIN" << std::endl;
            createUnixDomain();
            break;
        case TCP:
            std::cout << "CASE: TCP" << std::endl;
            createTcp();
            break;
        default:
            createUnixDomain();
            break;
    }
}

void
SocketClient::createUnixDomain() {
    std::cout << "SocketClient::createUnixDomain" << std::endl;
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
        close(server_);
    }
}

void
SocketClient::createTcp() {
    std::cout << "SocketClient::createTcp" << std::endl;
    try {
        struct sockaddr_in server_addr;
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(addr_.c_str());
        server_addr.sin_port = port_;
        server_ = socket(AF_INET, SOCK_STREAM, 0);
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
        close(server_);
    }
}

void
SocketClient::handle() {
    try {
        bool is_sent, is_success;
        is_sent = sendAck();
        if (!is_sent) throw;
        is_success = getResponse();
        if (!is_success) throw;
    } catch(...) {
        close(server_);
    }
}

bool
SocketClient::sendAck() {
    std::cout << "SocketClient::sendAck()" << std::endl;
    try {
        int ss;
        if ((ss = send(server_, &dpi_, sizeof(dpi_), 0)) < 0) {
            std::cerr << "send: " << std::endl;
            return false;
        } else {
            return true;
        }
    } catch(...) {
        close(server_);
        return false;
    }
}

bool
SocketClient::getResponse() {
    try {
        int gs;

        std::cout << "waiting response" << std::endl;
        if ((gs = recv(server_, &dpi_, sizeof(dpi_), 0)) < 0 ) {
            std::cerr << "recv";
            return false;
        } else {
            std::cout << "success: " << dpi_.data_ << std::endl;
            return true;
        }
    } catch(...) {
        close(server_);
        return false;
    }
}

