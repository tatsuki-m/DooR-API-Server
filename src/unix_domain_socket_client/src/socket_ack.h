#ifndef SOCKET_ACK_H_
#define SOCKET_ACK_H_

enum SocketType {
    ASK_SOCKET = 0,
    ASK_SHM= 1,
    STOP_SOCKET_SERVER = 99,
};

struct SocketAck {
    SocketType type;
    char data[64] = {'\0'};
};

#endif

