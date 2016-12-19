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
    std::cout << "SharedMemory::write()" << std::endl;
    shared_memory_object shm(open_or_create, m_sharedMemoryName_, read_write);
    shm.truncate(sizeof(U)+U::getSharedDataSize());
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = new (addr) U;

    try {
        while(true) {
            m_sharedMemoryBuffer_->writer_.wait();
                std::cout << "start writing" << std::endl;
              /*
                m_sharedMemoryBuffer_->sharedData_.id_ = sharedData->id_;
                m_sharedMemoryBuffer_->sharedData_.srcPort_= sharedData->srcPort_;
                m_sharedMemoryBuffer_->sharedData_.dstPort_ = sharedData->dstPort_;
                std::cout << "memory id " << m_sharedMemoryBuffer_->sharedData_.id_ << std::endl;
              */

                //memcpy(m_sharedMemoryBuffer_->sharedData_, sharedData, U::getSharedDataSize());
                m_sharedMemoryBuffer_->writeDataToShm(sharedData);
                std::cout << "m_sharedMemoryBuffer_->sharedData_.id_: " << m_sharedMemoryBuffer_->sharedData_.id_ << std::endl;
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
    std::cout << "SharedMemory::read()" << std::endl;
    shared_memory_object shm(open_only, m_sharedMemoryName_, read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = static_cast<U*>(addr);

    try {
        m_sharedMemoryBuffer_->reader_.wait();
            std::cout << "start reading" << std::endl;
            //*sharedData  = new T[U::getSharedDataSize()];
            //memcpy(*sharedData, m_sharedMemoryBuffer_->sharedData_, U::getSharedDataSize());
            /*
            *sharedData = new T;
            std::cout << "sharedData: " << (*sharedData)->id_ << std::endl;
            std::cout << "m_shareMemoryBuffer: " << m_sharedMemoryBuffer_->sharedData_.id_ << std::endl;
            (*sharedData)->id_ =  m_sharedMemoryBuffer_->sharedData_.id_;
            (*sharedData)->srcPort_ =  m_sharedMemoryBuffer_->sharedData_.srcPort_;
            (*sharedData)->dstPort_ =  m_sharedMemoryBuffer_->sharedData_.dstPort_;
            */
          *sharedData = new T;
          m_sharedMemoryBuffer_->readDataFromShm(*sharedData);
          //memcpy(*sharedData, m_sharedMemoryBuffer_->sharedData_, U::getSharedDataSize());
        m_sharedMemoryBuffer_->writer_.post();
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
    }
}

// Instantiation of explicit template
//template class SharedMemory<char, SharedKey>;
//template class SharedMemory<char, SharedPacketInformation>;
template class SharedMemory<Dpi, SharedPacketInformation>;
//template class SharedMemory<Dpi2, SharedPacketInformation>;

