#include "door_api.h"

std::string DOOR_BASE_SOCKET_NAME = "/tmp/unix-socket-door";

DoorApi::DoorApi() {
}

DoorApi::~DoorApi() {
}

void
DoorApi::callDoorWithSem(std::string shmKey, std::string keyword) {
    SocketType type = ASK_DOOR;
    UnixDomainSocketClient socket = UnixDomainSocketClient(DOOR_BASE_SOCKET_NAME, type, shmKey);
    socket.run();

/*
    SharedMemory<Dpi, SharedPacketInformation>* doorShm = new SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    Dpi *dpi;
    doorShm->read(&dpi);
*/
}

