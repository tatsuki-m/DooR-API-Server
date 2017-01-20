#include "door_api.h"

std::string DOOR_BASE_SOCKET_NAME = "/tmp/unix-socket/door-unix-socket";

DoorApi::DoorApi() {
}

DoorApi::~DoorApi() {
}

bool
DoorApi::callDoor(std::string shmKey, DoorSocketType type) {
    bool is_success;
    DoorUnixDomainSocketClient socket = DoorUnixDomainSocketClient(DOOR_BASE_SOCKET_NAME, type, shmKey);
    is_success =  socket.run();
    return is_success;
}

