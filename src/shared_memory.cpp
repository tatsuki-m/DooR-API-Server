#include "shared_memory.h"

template <class T, class U>
SharedMemory<T, U>::SharedMemory(std::string sharedMemoryName) {
    m_sharedMemoryName_ = sharedMemoryName.c_str();
}

template <class T, class U>
SharedMemory<T, U>::~SharedMemory() {
    // TODO: check shared memory is already deleted 
}

template <class T, class U>
T
SharedMemory<T, U>::read() {
    std::cout << "reading" << std::endl;
    shared_memory_object shm(open_only, m_sharedMemoryName_, read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = static_cast<U*>(addr);

    try {
        m_sharedMemoryBuffer_->reader_.wait();
            T sharedData = m_sharedMemoryBuffer_->getSharedData();
        m_sharedMemoryBuffer_->writer_.post();
        return sharedData;
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
}

template <class T, class U>
bool
SharedMemory<T, U>::write(T sharedData) {
    std::cout << "writing" << std::endl;
    shared_memory_object shm(open_or_create, m_sharedMemoryName_, read_write);
    shm.truncate(sizeof(T));
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = new (addr) U;

    try {
        while(true) {
            m_sharedMemoryBuffer_->writer_.wait();
                strcpy(m_sharedMemoryBuffer_->getSharedData(), sharedData);
            m_sharedMemoryBuffer_->reader_.post();
        };
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
    return true;
}

// Instantiation of explicit template
template class SharedMemory<char*, SharedKey>;
template class SharedMemory<char*, SharedPacketInformation>;

