#include "door_api_worker.h"

DoorApiWorker::DoorApiWorker(unsigned int workerID, std::string sharedMemoryName)
    : abort_(false), instanceNum_(0), id_(workerID), th_(&DoorApiWorker::run, this, sharedMemoryName) {
}

DoorApiWorker::~DoorApiWorker() {
    if (m_sharedMemoryBuffer != NULL) {
        shared_memory_object::remove(m_sharedMemoryName_);
        delete m_sharedMemoryBuffer;
    }
}

void
DoorApiWorker::run(std::string sharedMemoryName) {
    std::cout << "DoorApiWorker::run: " << std::this_thread::get_id() << std::endl;
    std::cout << "+ Woker::run" << std::endl;

    // initialize attribute
    strcpy(m_sharedMemoryName_, sharedMemoryName.c_str());
    writeSharedMemory();
    // write key to shared memory

    while (true) {
        std::unique_lock<std::mutex> lock(mtx_);
        auto sleep_time = std::chrono::seconds(1);
        if (abort_) {
            std::cout << "aborted" << std::endl;
            break;
        };
        cv_.wait_for(lock, sleep_time, [this] { return abort_; });
    }
    std::cout << "-Worker::run" << std::endl;
}

bool
DoorApiWorker::writeSharedMemory() {
    std::cout << "DoorApiWorker::writeSharedMemory()" << std::endl;
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
                //std::string doorShmKey = KeyGenerator::createKey(m_sharedMemoryName_, instanceNum_);
                //strcpy(m_sharedMemoryBuffer->doorShmKey, doorShmKey.c_str());
                std::cout << "doorShmKey: " << m_sharedMemoryBuffer->doorShmKey << std::endl;
            m_sharedMemoryBuffer->reader.post();
        };
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
    return true;
}

