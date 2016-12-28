#ifndef DOOR_API_H_
#define DOOR_API_H_

#include <iostream>
#include <string>

#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/dpi.h"

class DoorApi
{
public:
    DoorApi();
    ~DoorApi();
    bool getAllInformation(std::string, std::string);
private:
};


#endif

