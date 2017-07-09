#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
    workerId_ = 0;
}

DoorApiManager::~DoorApiManager() {
    // delete door worker api
    //std::for_each(doorApiWorkers.begin(), doorApiWorkers.end(),
     //             [](DoorApiWorker* p) { delete p; });
    //doorApiWorkers.clear();
    workerMap.clear();
}

void
DoorApiManager::create(std::string socketName) {
    std::cout << "DoorApiManger::create: generate worker" << std::endl;
    std::cout << "SocketName: " << socketName << std::endl;
    workerId_++;
    DoorApiWorker *worker = new DoorApiWorker(workerId_, socketName);
    //doorApiWorkers.push_back(worker);
    workerMap.insert(std::make_pair(workerId_, worker));
}

bool
DoorApiManager::destroy(unsigned int workerId) {
    std::cout << "DoorApiManger::destroy: destroy" << std::endl;
    std::cout << "DoorApiManger::create: generate worker" << std::endl;

    // =============sample code
    std::string socketName = "/tmp/hoge";
    workerId_++;
    DoorApiWorker* worker = new DoorApiWorker(workerId_, socketName);
    std::cout << "worker id: " << worker->id_ << std::endl;
    std::cout << "worker" << worker << std::endl;
    //doorApiWorkers.push_back(worker);
    workerMap.insert(std::make_pair(workerId_, worker));
    sleep(1);
    // ============
    std::cout << "size: " << workerMap.size() << std::endl;

    try {
        // errorはserver側でかえすので、例外をはくatは使用しない方向で行く
        DoorApiWorker *worker2 = workerMap.at(workerId);
        std::cout << worker2->id_ << std::endl;
        delete worker2;
        //workerMap.erase(workerId);
    }  catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << std::endl;
        exit(0);
    }
    //DoorApiWorker *worker2 = workerMap.at(workerId);
    //delete worker2;
    //std::cout << "worker2: " << worker2 << std::endl;
    //std::cout << "delete worker" << std::endl;
    //workerMap.erase(workerId);
}

