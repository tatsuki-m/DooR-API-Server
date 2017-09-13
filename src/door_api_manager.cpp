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
    std::cout << "DoorApiManger::destroy: " << std::endl;

    // =============sample code
    std::string socketName = "/tmp/hoge";
    workerId_++;
    std::cout << "Number: " << workerId_ << std::endl;
    DoorApiWorker* worker = new DoorApiWorker(workerId_, socketName);
    workerMap.insert(std::make_pair(workerId_, worker));
    // ============
    std::cout << "size: " << workerMap.size() << std::endl;

    try {
        sleep(1);
        //DoorApiWorker *worker2 = workerMap.find(workerId);
        // atにすると二回目にエラーが生じる
        DoorApiWorker *worker2 = workerMap.at(workerId);
        worker2->stopWorkerSocketServer();
        std::cout << "Number2: " << workerId_ << std::endl;
        delete worker2;
        workerMap.erase(workerId);
        std::cout << "size: " << workerMap.size() << std::endl;
    }  catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range error: " << oor.what() << std::endl;
        exit(0);
    }
}

