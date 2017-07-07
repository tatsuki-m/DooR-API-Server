#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
    workerId_ = 0;
}

DoorApiManager::~DoorApiManager() {
    // delete door worker api
    std::for_each(doorApiWorkers.begin(), doorApiWorkers.end(),
                  [](DoorApiWorker* p) { delete p; });
    doorApiWorkers.clear();
}

void
DoorApiManager::create(std::string socketName) {
    std::cout << "DoorApiManger::create: generate worker" << std::endl;
    std::cout << "SocketName: " << socketName << std::endl;
    workerId_++;
    DoorApiWorker *worker = new DoorApiWorker(workerId_, socketName);
    doorApiWorkers.push_back(worker);
}

bool
DoorApiManager::destroy(unsigned int workerId) {
    std::cout << "DoorApiManger::create: generate worker" << std::endl;
    return true;

}

