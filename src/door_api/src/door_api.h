#ifndef DOOR_API_H_
#define DOOR_API_H_

#include <iostream>
#include <string>

#include "door_unix_domain_socket_client.h"
#include "door_socket.h"

class DoorApi
{
public:
    DoorApi();
    ~DoorApi();
    bool callDoorWithSem(std::string);
private:
};


#endif

