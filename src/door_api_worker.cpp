#include "door_api_worker.h"

DoorApiWorker::DoorApiWorker(std::string sharedMemoryName) {
    std::cout << "DoorApiWorker" << std::this_thread::get_id() << std::endl;
    strcpy(m_sharedMemoryName_, sharedMemoryName.c_str());
    instanceNum_ = 0;

    // initSharedMemory();
}

DoorApiWorker::~DoorApiWorker() {
    if (m_sharedMemoryBuffer != NULL) {
        shared_memory_object::remove(m_sharedMemoryName_);
        delete m_sharedMemoryBuffer;
    }
}

bool
DoorApiWorker::initSharedMemory() {
    // use old  shared memory if exists else create a new one
    shared_memory_object shm(open_or_create, m_sharedMemoryName_, read_write);
    // set the size of the memory object
    shm.truncate(sizeof(SharedMemoryBuffer));
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    // creat a shared memory buffer in memory
    m_sharedMemoryBuffer = new (addr) SharedMemoryBuffer;

    try {
        // waiting creation of DoorApi instance
        while (true) {
            // wait until the written number gets executed
            m_sharedMemoryBuffer->writer.wait();
                instanceNum_++;
                strcpy(m_sharedMemoryBuffer->appShmKey, getAppShmKey().c_str());
                std::cout << m_sharedMemoryBuffer->appShmKey << std::endl;
            m_sharedMemoryBuffer->reader.post();
        };
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
    return true;
}

std::string
DoorApiWorker::getAppShmKey() {
    std::string appShmKey = m_sharedMemoryName_ + std::to_string(instanceNum_);
    return appShmKey;
}

