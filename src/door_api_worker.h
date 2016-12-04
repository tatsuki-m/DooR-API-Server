#ifndef DOOR_API_WORKER_H_
#define DOOR_API_WORKER_H_

#include <iostream>
#include <sstream> /* ostringstream */
#include <iomanip> /* setfill, setw */
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "worker.h"

using namespace boost::interprocess;

class DoorApiWorker
{
    struct SharedMemoryBuffer {
        // writer inialized with one to start
        // reader have to wait
        SharedMemoryBuffer(): writer(1), reader(0) {}
        interprocess_semaphore writer, reader;
        char appShmKey[16];
    };

public:
    DoorApiWorker(std::string);
    ~DoorApiWorker();
private:
    void run(std::string);
    bool initSharedMemory();
    std::string getAppShmKey();

    // variable for shared memory
    SharedMemoryBuffer *m_sharedMemoryBuffer;

    bool abort_;
    std::mutex mtx_;
    std::condition_variable cv_;
    std::thread th_;
    char m_sharedMemoryName_[16];
    unsigned int instanceNum_;
};

#endif

