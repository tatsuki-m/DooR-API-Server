#ifndef DOOR_API_H_
#define DOOR_API_H_

#include <iostream>
#include <string>

#include "unix_domain_socket_client.h"

#include "door_bridge/socket_ack.h"
#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/dpi.h"

class DoorApi
{
public:
    DoorApi();
    ~DoorApi();
    void callDoorWithSem(std::string, std::string);
private:
};


#endif

