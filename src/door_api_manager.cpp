#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
    shmKey_ = 0;
}

DoorApiManager::~DoorApiManager() {
}

void
DoorApiManager::create(int key) {
    shmKey_ = key;
    std::cout << "data = " << key << std::endl;
    std::cout << "worker start" << std::endl;

    DoorApiWorker worker1;
    DoorApiWorker worker2;

}

std::string
DoorApiManager::getShmKey(int key) {
}

