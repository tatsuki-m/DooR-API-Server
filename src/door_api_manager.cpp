#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
}

DoorApiManager::~DoorApiManager() {
}

void
DoorApiManager::create(std::string doorBaseShmKey) {
    DoorApiWorker *worker = new DoorApiWorker(doorBaseShmKey);
    p_doorApiWorkers.push_back(worker);

    std::cout << "generate worker" << std::endl;
    /*
    while (true) {
        std::cout << worker->m_sharedSt_.value << " " << worker->m_sharedSt_.valueFloat << std::endl;
        sleep(1);
    }
    */
    // delete worker;
}

