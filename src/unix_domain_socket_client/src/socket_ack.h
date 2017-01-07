#ifndef SOCKET_ACK_H_
#define SOCKET_ACK_H_

enum SocketType {
    ASK_SOCKET = 0,
    ASK_SHM= 1,
    ASK_DOOR = 2,
};

struct SocketAck {
    SocketType type;
    char data[64] = {'\0'};
};

#endif

