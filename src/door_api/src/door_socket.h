#ifndef DOOR_SOCKET_H_
#define DOOR_SOCKET_H_

enum DoorSocketType {
    SHM = 0,
    UD_SOCK = 1,
    TCP_SOCK = 2,
};

struct DoorSocket {
    DoorSocketType  type;
    char data[16] = {'\0'};
    char ipAddress[16] = {'\0'};
    unsigned int port = 0;
};

#endif

