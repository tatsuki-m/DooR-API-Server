#ifndef DOOR_API_WORKER_H_
#define DOOR_API_WORKER_H_

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "key_generator.h"

using namespace boost::interprocess;

class DoorApiWorker
{
    struct SharedMemoryBuffer {
        // writer inialized with one to start
        // reader have to wait
        SharedMemoryBuffer(): writer(1), reader(0) {}
        interprocess_semaphore writer, reader;
        char doorShmKey[16];
    };

public:
    DoorApiWorker(unsigned int, std::string);
    ~DoorApiWorker();
private:
    void run(std::string);
    bool writeSharedMemory();
    std::string getAppShmKey();

    // variable for shared memory
    SharedMemoryBuffer *m_sharedMemoryBuffer;
    char m_sharedMemoryName_[16];
    unsigned int id_;
    unsigned int instanceNum_;
    bool abort_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::thread th_;
};

#endif

