#include "shared_memory.h"

template <class T, class U>
SharedMemory<T, U>::SharedMemory(std::string sharedMemoryName) {
    sharedMemoryName_ = sharedMemoryName.c_str();
}

template <class T, class U>
SharedMemory<T, U>::~SharedMemory() {
    // TODO: check shared memory is already deleted
}

template <class T, class U>
void
SharedMemory<T, U>::write(T* sharedData) {
    int counter = 0;
    std::cout << "SharedMemory::write()" << std::endl;
    shared_memory_object shm(open_or_create, sharedMemoryName_.c_str(), read_write);
    shm.truncate(sizeof(U)+U::getSharedDataSize());
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = new (addr) U;

    try {
      std::cout << "==========================" << std::endl;
      std::cout << "start writing" << std::endl;
      std::cout << "==========================" <<  std::endl;
       while(counter<1000) {
          m_sharedMemoryBuffer_->writer_.wait();
              m_sharedMemoryBuffer_->writeDataToShm(sharedData);
              counter++;
              std::cout << "counter: " << counter << std::endl;
          m_sharedMemoryBuffer_->reader_.post();
       }
      std::cout << "==========================" << std::endl;
      std::cout << "finish writing" << std::endl;
      std::cout << "==========================" << std::endl;
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
   }
}

template <class T, class U>
bool
SharedMemory<T, U>::read(T** sharedData) {
    std::cout << "SharedMemory::read()" << std::endl;
    shared_memory_object shm(open_or_create, sharedMemoryName_.c_str(), read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = static_cast<U*>(addr);

    try {
      std::cout << "==========================" << std::endl;
      std::cout << "start reading" << std::endl;
      std::cout << "==========================" <<  std::endl;
      while(true) {
          m_sharedMemoryBuffer_->reader_.wait();
              *sharedData = new T;
              m_sharedMemoryBuffer_->readDataFromShm(*sharedData);
              std::cout << "SharedMemory::read sharedData: " << (*sharedData)->id_ << std::endl;
          m_sharedMemoryBuffer_->writer_.post();
      }
      std::cout << "==========================" << std::endl;
      std::cout << "finish reading" << std::endl;
      std::cout << "==========================" <<  std::endl;
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

// Instantiation of explicit template
//template class SharedMemory<char, SharedKey>;
template class SharedMemory<Dpi, SharedPacketInformation>;

