#ifndef DOOR_API_WORKER_H_
#define DOOR_API_WORKER_H_

#include <iostream>
#include <string>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "worker.h"

using namespace boost::interprocess;

class DoorApiWorker : public Worker
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
    bool run();

private:
    bool initSharedMemory();
    std::string getAppShmKey();

    // variable for shared memory
    SharedMemoryBuffer *m_sharedMemoryBuffer;
    char m_sharedMemoryName_[16];
    unsigned int instanceNum_;
};

#endif

