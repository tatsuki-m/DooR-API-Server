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
    shm.truncate(sizeof(U)+U::getSharedDataSize());
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = new (addr) U;

    try {
        while(true) {
            std::cout << "start writing" << std::endl;
            m_sharedMemoryBuffer_->writer_.wait();
                memcpy(m_sharedMemoryBuffer_->sharedData_, sharedData, U::getSharedDataSize());
            m_sharedMemoryBuffer_->reader_.post();
        };
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
   }
    return true;
}

template <class T, class U>
void
SharedMemory<T, U>::read(T** sharedData) {
    std::cout << "read()" << std::endl;
    shared_memory_object shm(open_only, m_sharedMemoryName_, read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = static_cast<U*>(addr);

    try {
        std::cout << "start reading" << std::endl;
        m_sharedMemoryBuffer_->reader_.wait();
            *sharedData  = new T;
            std::cout << U::getSharedDataSize() << std::endl;
            std::cout << sizeof(Dpi) << std::endl;
            /*
            char data[1000] = "hoge";
            char ipdata[10] = "hoge";
            Dpi* dpi = new Dpi(1, ipdata, ipdata, 2, 3, data);
            memcpy(*sharedData, dpi, U::getSharedDataSize());
            */
            memcpy(*sharedData, m_sharedMemoryBuffer_->sharedData_, U::getSharedDataSize());
        m_sharedMemoryBuffer_->writer_.post();
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
}

// Instantiation of explicit template
template class SharedMemory<char, SharedKey>;
template class SharedMemory<char, SharedPacketInformation>;
// template class SharedMemory<Dpi, SharedPacketInformation>;

