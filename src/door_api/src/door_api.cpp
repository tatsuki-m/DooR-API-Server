#include "door_api.h"

std::string DOOR_BASE_SOCKET_NAME = "/tmp/door-unix-socket";

DoorApi::DoorApi() {
}

DoorApi::~DoorApi() {
}

void
DoorApi::callDoorWithSem(std::string shmKey, std::string keyword) {
    SocketType type = ASK_DOOR;
    UnixDomainSocketClient socket = UnixDomainSocketClient(DOOR_BASE_SOCKET_NAME, type, shmKey);
    socket.run();
}

