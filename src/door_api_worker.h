#ifndef DOOR_API_WORKER_
#define DOOR_API_WORKER_

#include <iostream>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class DoorApiWoker
{
public:
    DoorApiWoker();
    virtual ~DoorApiWorker();
    void abort_thread();

private:
    bool abort_;
    std::mutext mtx_;
    std::condition_variable cv_;
    std::thread th_;

    void run();
    void thread_proc();
}

#endif

