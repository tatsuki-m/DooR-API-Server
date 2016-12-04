#include "worker.h"

Worker::Worker() : abort_(false), th_(&Worker::run, this)  {
    std::cout << "Worker" << std::this_thread::get_id() << std::endl;
}

Worker::~Worker() {
    std::cout << "+Worker::~Woker" << std::endl;
    abortThread();
    th_.join();
    std::cout << "-Worker::~Woker" << std::endl;
}

void
Worker::abortThread() {
    std::lock_guard<std::mutex> lock(mtx_);

    if (!abort_) {
        std::cout << "notify abort event" << std::endl;
        abort_ = true;
        cv_.notify_all();
    }
}

void
Worker::run() {
    std::cout << "run: " << std::this_thread::get_id() << std::endl;
    std::cout << "+Woker::run" << std::endl;
    while (true) {
        std::unique_lock<std::mutex> lock(mtx_);
        auto sleep_time = std::chrono::seconds(1);
        if (abort_) {
            std::cout << "aborted" << std::endl;
            break;
        };
        threadProc();
        cv_.wait_for(lock, sleep_time, [this] { return abort_; });
    }
    std::cout << "-Worker::run" << std::endl;
}

void
Worker::threadProc() {
   std::cout << "Thread run! " << std::this_thread::get_id() << std::endl;
}

