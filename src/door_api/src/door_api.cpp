#include "door_api.h"

DoorApi::DoorApi() {
}

DoorApi::~DoorApi() {
}

void
DoorApi::getAllInformation(std::string shmKey, std::string keyword) {
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    // create stub door data
    unsigned int id = 100;
    unsigned int srcPort = 1;
    unsigned int dstPort = 1;
    Dpi dpi = Dpi(id, srcPort, dstPort);
    std::cout << "DoorApi::getAllInformation dpi writing" << std::endl;
    doorShm.write(&dpi);
}



