#ifndef SOCKET_ACK_H_
#define SOCKET_ACK_H_

enum SocketType {
    ASK_SOCKET = 0,
    ASK_SHM= 1,
};

struct SocketAck {
    char data[64] = {'\0'};
    SocketType type;
};

#endif
