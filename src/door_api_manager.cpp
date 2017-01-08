#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
    workerNum_ = 0;
}

DoorApiManager::~DoorApiManager() {
    // delete door worker api
    std::for_each(doorApiWorkers.begin(), doorApiWorkers.end(), [](DoorApiWorker* p) { delete p; });
    doorApiWorkers.clear();
}

void
DoorApiManager::create(std::string socketName) {
    std::cout << "DoorApiManger::create: generate worker" << std::endl;
    std::cout << "SocketName: " << socketName << std::endl;
    workerNum_++;
    DoorApiWorker *worker = new DoorApiWorker(workerNum_, socketName);
    doorApiWorkers.push_back(worker);
}

