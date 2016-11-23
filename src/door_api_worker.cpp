#include "door_api_worker.h"

DoorApiWorker::DoorApiWorker() : abort_(false), th_(&DoorApiWorker::run, this)  {
}

DoorApiWorker::~DoorApiWorker() {
    std::cout << "+Worker::~Woker" << std::endl;
    abortThread();
    th_.join();
    std::cout << "-Worker::~Woker" << std::endl;
}

void
DoorApiWorker::abortThread() {
    std::lock_guard<std::mutex> lock(mtx_);

    if (!abort_) {
        std::cout << "notify abort event" << std::endl;
        abort_ = true;
        cv_.notify_all();
    }
}

void
DoorApiWorker::run() {
    std::cout << "+Woker::run" << std::endl;

    while (true) {
        // std::unique_lock<std::mutex> lock(mtx_);
        // auto sleep_time = std::chrono::seconds(1);

        if (abort_) {
            std::cout << "aborted" << std::endl;
            break;
        }
        threadProc();

        // select sleeptime
        // cv_.wait_for(lock, sleep_time, [this] { return abort_; });
    }

    std::cout << "-Worker::run" << std::endl;
}

void
DoorApiWorker::threadProc() {
    std::cout << "Thread run!" << std::endl;
}
