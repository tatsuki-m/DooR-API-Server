#include "shared_memory.h"

template <class T, class U>
SharedMemory<T, U>::SharedMemory(std::string sharedMemoryName) {
    m_sharedMemoryName_ = sharedMemoryName.c_str();
}

template <class T, class U>
SharedMemory<T, U>::~SharedMemory() {
    // TODO: check shared memory is already deleted 
    delete m_sharedMemoryName_;

}

template <class T, class U>
bool
SharedMemory<T, U>::write(T* sharedData) {
    std::cout << "write()" << std::endl;
    shared_memory_object shm(open_or_create, m_sharedMemoryName_, read_write);
    shm.truncate(sizeof(U));
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = new (addr) U;

    try {
        while(true) {
            std::cout << "start writing" << std::endl;
            m_sharedMemoryBuffer_->writer_.wait();
                std::cout << "writer post" << std::endl;
                memcpy(m_sharedMemoryBuffer_->sharedData_, sharedData, 100/*sizeof(T*)*/);
            m_sharedMemoryBuffer_->reader_.post();
        };
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
    return true;
}

template <class T, class U>
T*
SharedMemory<T, U>::read() {
    std::cout << "read()" << std::endl;
    shared_memory_object shm(open_only, m_sharedMemoryName_, read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = static_cast<U*>(addr);

    try {
        std::cout << "start reading" << std::endl;
        m_sharedMemoryBuffer_->reader_.wait();
            T* sharedData = m_sharedMemoryBuffer_->sharedData_;
            std::cout << sharedData << std::endl;
        m_sharedMemoryBuffer_->writer_.post();
        return sharedData;
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
}


// Instantiation of explicit template
template class SharedMemory<char, SharedKey>;
template class SharedMemory<Dpi, SharedPacketInformation>;

