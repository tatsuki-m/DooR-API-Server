#ifndef DOOR_API_WORKER_H_
#define DOOR_API_WORKER_H_

#include <iostream>
#include <string>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>

#include "worker.h"

using namespace boost::interprocess;

class DoorApiWorker : public Worker
{
    struct SharedSt {
        int value;
        double valueFloat;
    };

public:
    DoorApiWorker(std::string);
    ~DoorApiWorker();

    bool initSharedMemory();
    bool getStruct();

    SharedSt m_sharedSt_;

private:
    managed_shared_memory *m_shm_;
    char m_sharedMemoryName_[32];
};

#endif

