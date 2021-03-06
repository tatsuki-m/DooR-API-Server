#ifndef SHARED_MEMORY_H_
#define SHARED_MEMORY_H_

#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <iomanip>

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "time_recorder.h"
#include "shared_packet_information.h"
#include "shared_key.h"
#include "dpi.h"
#include "sync_semaphore.h"

template <class T, class U=SharedPacketInformation> // T=shared data structure, U=Shared class with semaphore
class SharedMemory
{
public:
    SharedMemory(std::string);
    ~SharedMemory();
    void write(T*);
    bool read(T**);
    void removeSharedMemory();
private:
    std::string sharedMemoryName_;
    U* m_sharedMemoryBuffer_;
};


#endif

