#include "shared_memory.h"

template <class T, class U>
SharedMemory<T, U>::SharedMemory(std::string sharedMemoryName) {
    m_sharedMemoryName_ = sharedMemoryName.c_str();
}

template <class T, class U>
SharedMemory<T, U>::~SharedMemory() {
    // TODO: check shared memory is already deleted 
}

template class SharedMemory<std::string, SharedKey>;
template class SharedMemory<std::string, SharedPacketInformation>;

