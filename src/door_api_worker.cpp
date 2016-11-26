#include "door_api_worker.h"

DoorApiWorker::DoorApiWorker(std::string sharedMemoryName) {
    strcpy(m_sharedMemoryName_, sharedMemoryName.c_str());
    m_shm_ = NULL;
}

DoorApiWorker::~DoorApiWorker() {
    if (m_shm_ != NULL)  delete m_shm_;
}

bool
DoorApiWorker::initSharedMemory() {
    int m_size;
    m_size = sizeof(SharedSt) + 1024 * 10;
    std::cout << m_size << "byte" << std::endl;

    m_shm_ = new managed_shared_memory(open_or_create, m_sharedMemoryName_, m_size);
    std::cout << "memory share!" << std::endl;

     return true;
}


bool
DoorApiWorker::getStruct() {
    if( m_shm_ == NULL)
        return false;

    interprocess_mutex *mx = m_shm_->find_or_construct<interprocess_mutex>("TheMutex")();
    SharedSt* SharedMemoryPointer = m_shm_->find_or_construct<SharedSt>("SharedSt")();

    scoped_lock<interprocess_mutex> *lock = new scoped_lock<interprocess_mutex>(*mx);
    memcpy( &m_sharedSt_, SharedMemoryPointer, sizeof(SharedSt));
    delete lock;
    return true;
}

