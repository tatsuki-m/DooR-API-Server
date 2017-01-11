#include "shared_memory.h"

const int MAX_COUNT = 1000;

template <class T, class U>
SharedMemory<T, U>::SharedMemory(std::string sharedMemoryName) {
    sharedMemoryName_ = sharedMemoryName.c_str();
}

template <class T, class U>
SharedMemory<T, U>::~SharedMemory() {
}

template <class T, class U>
void
SharedMemory<T, U>::removeSharedMemory() {
    shared_memory_object::remove(sharedMemoryName_.c_str());
}


template <class T, class U>
void
SharedMemory<T, U>::write(T* sharedData) {
    int counter = 0;
    std::ofstream ofs("Test.csv");
    struct timespec startTime, endTime;
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
       while(counter<MAX_COUNT) {
          clock_gettime(CLOCK_MONOTONIC, &startTime);
          m_sharedMemoryBuffer_->writer_.wait();
              m_sharedMemoryBuffer_->writeDataToShm(sharedData);
              counter++;
          m_sharedMemoryBuffer_->reader_.post();
          clock_gettime(CLOCK_MONOTONIC, &endTime);
          ofs << startTime.tv_sec << std::setfill('0') << std::setw(6) << std::right << startTime.tv_nsec<<",";
          ofs << endTime.tv_sec << std::setfill('0') << std::setw(6) << std::right << endTime.tv_nsec<<",";
          ofs << std::setfill('0') << std::setw(6) << std::right << startTime.tv_nsec << "," << std::setfill('0') << std::setw(6) << endTime.tv_nsec << std::endl;
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
    int counter = 0;
    std::cout << "SharedMemory::read()" << std::endl;
    shared_memory_object shm(open_or_create, sharedMemoryName_.c_str(), read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = static_cast<U*>(addr);

    try {
      std::cout << "==========================" << std::endl;
      std::cout << "start reading" << std::endl;
      std::cout << "==========================" <<  std::endl;
      while(counter<MAX_COUNT) {
          m_sharedMemoryBuffer_->reader_.wait();
              *sharedData = new T;
              m_sharedMemoryBuffer_->readDataFromShm(*sharedData);
              counter++;
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
template class SharedMemory<char, SharedKey>;
template class SharedMemory<Dpi, SharedPacketInformation>;

