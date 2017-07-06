#ifndef DPI_SOCKET_H_
#define DPI_SOCKET_H_

enum ConType {
    UNIX_DOMAIN = 1,
    TCP = 2,
};

struct DpiSocket {
    char data[1514]  = {'\0'};
};

#endif

