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
    virtual void threadProc();
    void abortThread();

private:
    bool abort_;
    std::mutext mtx_;
    std::condition_variable cv_;
    std::thread th_;

    void run();
}

#endif

