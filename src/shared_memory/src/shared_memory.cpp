#include "shared_memory.h"

const int MAX_COUNT = 1000;
std::string BASE_RECORDER_DIR = "/tmp/recorder/";
std::string ENV = "native";

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
    //struct timespec startTime, endTime;
    //std::string fileName = BASE_RECORDER_DIR + ENV + "_" + std::to_string(U::getSharedDataSize()) + "_writer" + ".csv";
    //std::ofstream ofs(fileName.c_str());
    //ofs << "start_time, end_time, interval" << std::endl;
    //RecorderType type = WRITER;
    //TimeRecorder recorder(type, U::getSharedDataSize());
    std::cout << "SharedMemory::write()" << std::endl;
    shared_memory_object shm(open_or_create, sharedMemoryName_.c_str(), read_write);
    shm.truncate(U::getSharedDataSize());
    std::cout << "datasize: " << U::getSharedDataSize() << std::endl;
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = new (addr) U;

    try {
      std::cout << "==========================" << std::endl;
      std::cout << "start writing" << std::endl;
      std::cout << "==========================" <<  std::endl;
      while(counter<MAX_COUNT) {
          //clock_gettime(CLOCK_MONOTONIC, &startTime);
          //recorder.pushStartTime();
          m_sharedMemoryBuffer_->writer_.wait();
              m_sharedMemoryBuffer_->writeDataToShm(sharedData);
              counter++;
          m_sharedMemoryBuffer_->reader_.post();
          //clock_gettime(CLOCK_MONOTONIC, &endTime);
          //recorder.pushEndTime();
          /*
          ofs << std::setfill('0') << std::setw(6) << std::right << startTime.tv_nsec << ",";
          ofs << std::setfill('0') << std::setw(6) << endTime.tv_nsec << ",";
          ofs << endTime.tv_nsec - startTime.tv_nsec << std::endl;
          */
    }
    //recorder.record();
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
    /*
    struct timespec startTime, endTime;
    std::string fileName = BASE_RECORDER_DIR + ENV + "_" + std::to_string(U::getSharedDataSize()) + "_reader" + ".csv";
    std::ofstream ofs(fileName.c_str());
    ofs << "start_time, end_time, interval" << std::endl;
    */
    //RecorderType type = READER;
    //TimeRecorder recorder(type, U::getSharedDataSize());
    shared_memory_object shm(open_only, sharedMemoryName_.c_str(), read_write);
    mapped_region region(shm, read_write);
    void *addr = region.get_address();
    m_sharedMemoryBuffer_ = static_cast<U*>(addr);

    try {
//      while(counter<MAX_COUNT) {
          //clock_gettime(CLOCK_MONOTONIC, &startTime);
          //recorder.pushStartTime();
          m_sharedMemoryBuffer_->reader_.wait();
              *sharedData = new T;
              m_sharedMemoryBuffer_->readDataFromShm(*sharedData);
          //clock_gettime(CLOCK_MONOTONIC, &endTime);
          //recorder.pushEndTime();
          m_sharedMemoryBuffer_->writer_.post();
          /*
          ofs << std::setfill('0') << std::setw(6) << std::right << startTime.tv_nsec << ",";
          ofs << std::setfill('0') << std::setw(6) << endTime.tv_nsec << ".";
          ofs << endTime.tv_nsec - startTime.tv_nsec << std::endl;
          */
//      }
      //recorder.record();
    } catch (interprocess_exception& e) {
        std::cout << e.what() << std::endl;
        return false;
    }
    return true;
}

// Instantiation of explicit template
//template class SharedMemory<char, SharedKey>;
template class SharedMemory<Dpi, SharedPacketInformation>;

