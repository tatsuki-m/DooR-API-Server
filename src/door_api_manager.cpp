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
    /*
    while (true) {
        std::cout << worker->m_sharedSt_.value << " " << worker->m_sharedSt_.valueFloat << std::endl;
        sleep(1);
    }
    */
    delete worker;
}

std::string
DoorApiManager::getShmKey(int key) {
    std::string shmKey = "shm_key" + std::to_string(key);
    return shmKey;
}

