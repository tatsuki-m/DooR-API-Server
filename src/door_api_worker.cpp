#include "door_api_worker.h"

DoorApiWorker::DoorApiWorker(unsigned int workerID, std::string socketName)
    : id_(workerID),
      socketName_(socketName.c_str()),
      th_(&DoorApiWorker::run, this, socketName) {
}

DoorApiWorker::~DoorApiWorker() {
    std::cout << "+ DoorApiWorker::~DoorApiWorker" << std::endl;
    th_.join();
    std::cout << "- DoorApiWorker::~DoorApiWorker" << std::endl;
}

void
DoorApiWorker::run(std::string socketName) {
    std::cout << "DoorApiWorker::run thread id: " << std::this_thread::get_id() << std::endl;
    std::cout << "+Woker::run" << std::endl;
    socketName_ =  socketName;
    WorkerUnixDomainSocketServer socket = WorkerUnixDomainSocketServer(socketName_, id_);
    // workerのでsocketの情報を参照することがない, 現行の実装ではスレッドセーフ
    // 今後そのようなことがあれば、スレッドセーフにする必要がある
    socket.run();
    std::cout << "-Worker::run" << std::endl;
}

void
DoorApiWorker::stopWorkerSocketServer() {
    std::cout << "DoorApiWorker::stopWorkerSocketServer" << std::endl;
    SocketType type = STOP_SOCKET_SERVER;
    UnixDomainSocketClient client = UnixDomainSocketClient(socketName_, type);
    client.run();
    std::cout << "fin" << std::endl;
}

