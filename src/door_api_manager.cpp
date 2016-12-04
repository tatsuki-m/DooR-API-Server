#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
}

DoorApiManager::~DoorApiManager() {
}

void
DoorApiManager::create(std::string shmKey) {
    std::cout << "data = " << shmKey << std::endl;
    DoorApiWorker *worker = new DoorApiWorker(shmKey);
    p_doorApiWorkers.push_back(worker);
    worker->initSharedMemory();

    std::cout << "generate worker" << std::endl;
    /*
    while (true) {
        std::cout << worker->m_sharedSt_.value << " " << worker->m_sharedSt_.valueFloat << std::endl;
        sleep(1);
    }
    */
    delete worker;
}

