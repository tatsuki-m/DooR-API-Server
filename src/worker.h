#ifndef WORKER_H_
#define WORKER_H_

#include <iostream>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class Worker
{
public:
    Worker();
    virtual ~Worker();
    virtual void threadProc();
    void abortThread();

private:
    bool abort_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::thread th_;

    void run();
};

#endif

