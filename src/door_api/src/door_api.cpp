#include "door_api.h"

std::string DOOR_BASE_SOCKET_NAME = "/tmp/unix-socket/door-unix-socket";

DoorApi::DoorApi() {
}

DoorApi::~DoorApi() {
}

bool
DoorApi::callDoorWithSem(std::string shmKey) {
    SocketType type = ASK_DOOR;
    UnixDomainSocketClient socket = UnixDomainSocketClient(DOOR_BASE_SOCKET_NAME, type, shmKey);
    socket.run();
    if (socket.hasResponse()) {
        return true;
    } else {
        return false;
    }
}

