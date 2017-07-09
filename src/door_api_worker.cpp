#include "door_api_worker.h"

DoorApiWorker::DoorApiWorker(unsigned int workerID, std::string socketName)
    : id_(workerID),
      socketName_(socketName.c_str()),
      socket_(WorkerUnixDomainSocketServer(socketName_, id_)),
      th_(&DoorApiWorker::run, this, socketName) {
}

DoorApiWorker::~DoorApiWorker() {
    std::cout << "DoorApiWorker::~DoorApiWorker" << std::endl;
    socket_.sendDestroy();
    std::cout << "fin" << std::endl;
    th_.join();
}

void
DoorApiWorker::run(std::string socketName) {
    std::cout << "DoorApiWorker::run thread id: " << std::this_thread::get_id() << std::endl;
    std::cout << "+ Woker::run" << std::endl;


    std::cout << "===========socketName===========" << socketName << std::endl;
    //socketName_ =  socketName.c_str();
    //WorkerUnixDomainSocketServer socket = WorkerUnixDomainSocketServer(socketName_, id_);
    // workerのでsocketの情報を参照することがない, 現行の実装ではスレッドセーフ
    // 今後そのようなことがあれば、スレッドセーフにする必要がある
    socket_.run();

    std::cout << "-Worker::run" << std::endl;
}

