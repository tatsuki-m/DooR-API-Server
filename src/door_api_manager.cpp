#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
    workerNum_ = 0;
}

DoorApiManager::~DoorApiManager() {
    // delete door worker api
}

void
DoorApiManager::create(std::string socketName) {
    std::cout << "DoorApiManger::create: generate worker" << std::endl;
    workerNum_++;
    DoorApiWorker *worker = new DoorApiWorker(workerNum_, socketName);
    p_doorApiWorkers.push_back(worker);
}

