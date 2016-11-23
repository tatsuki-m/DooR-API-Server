#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
}

DoorApiManager::~DoorApiManager() {
}

void
DoorApiManager::create(int key) {
    std::string shmKey = getShmKey(key);
    std::cout << "data = " << key << std::endl;
    std::cout << "worker start" << std::endl;
    std::cout << shmKey << std::endl;

    DoorApiWorker *worker = new DoorApiWorker(shmKey);
    std::cout << "generate worker" << std::endl;
    delete worker;
}

std::string
DoorApiManager::getShmKey(int key) {
    const std::string kBaseKey = "shm_key";
    std::string shmKey = kBaseKey + std::to_string(key);
    return shmKey;
}

