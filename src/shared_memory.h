#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_

#include <iostream>
#include <string>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "shared_packet_information.h"
#include "shared_key.h"
#include "dpi_rule.h"

template <class T, class U=SharedPacketInformation> // T=shared data structure, U=Shared class with semaphore
class SharedMemory
{
public:
    SharedMemory(std::string);
    ~SharedMemory();
    // T initReadKey();
    // bool initWriteKey(T);
private:
    // U *m_sharedMemoryBuffer;
    const char* m_sharedMemoryName_;
};
#endif

