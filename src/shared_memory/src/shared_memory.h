#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_

#include <iostream>
#include <string>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "shared_packet_information.h"
#include "shared_key.h"
#include "dpi.h"

template <class T, class U=SharedPacketInformation> // T=shared data structure, U=Shared class with semaphore
class SharedMemory
{
public:
    SharedMemory(std::string);
    ~SharedMemory();
    void write(T*);
    bool read(T**);
    T* sharedData_;
    U* m_sharedMemoryBuffer_;
private:
    std::string sharedMemoryName_;
};


#endif

