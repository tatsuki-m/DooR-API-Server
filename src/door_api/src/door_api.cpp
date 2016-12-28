#include "door_api.h"

DoorApi::DoorApi() {
}

DoorApi::~DoorApi() {
}

bool
DoorApi::getAllInformation(std::string shmKey, std::string keyword) {
    bool is_success;
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    // create stub door data
    unsigned int id = 100;
    unsigned int srcPort = 1;
    unsigned int dstPort = 1;
    Dpi* dpi = new Dpi(id, srcPort, dstPort);

    is_success = doorShm.write(dpi);
    delete dpi;

    if (is_success) {
        std::cout << "door api write success" << std::endl;
        return true;
    } else {
        return false;
    }
}



