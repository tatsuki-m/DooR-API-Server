#ifndef SOCKET_ACK_H_
#define SOCKET_ACK_H_

enum SocketType {
    SHARED_SOCKET = 0,
    SHARED_MEMORY = 1,
    SHARED_LIBRARY = 2,
};

struct SocketAck {
    char request='\0'; // not use now
    char data[64] = {'\0'};
    SocketType type;
};

#endif
