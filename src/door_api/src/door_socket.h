#ifndef DOOR_SOCKET_H_
#define DOOR_SOCKET_H_

enum DoorSocketType {
    SHM = 0,
    UNIX_DOMAIN_SOCKET = 1,
    TCP_SOCKET = 2,
};

struct DoorSocket {
    DoorSocketType  type;
    char data[16] = {'\0'};
    char ipAddress[16] = {'\0'};
    unsigned int port = 0;
};

#endif
