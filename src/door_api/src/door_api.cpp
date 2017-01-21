#include "door_api.h"

std::string DOOR_BASE_SOCKET_NAME = "/tmp/unix-socket/door-unix-socket";

DoorApi::DoorApi() {
}

DoorApi::~DoorApi() {
}

void
DoorApi::callDoor(std::string shmKey, DoorSocketType type) {
    DoorUnixDomainSocketClient socket = DoorUnixDomainSocketClient(DOOR_BASE_SOCKET_NAME, type, shmKey);
    socket.run();
}

