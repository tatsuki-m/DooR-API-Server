#ifndef SHARED_PACKET_INFORMATION_H_
#define SHARED_PACKET_INFORMATION_H_

#include <iostream>
#include <string>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "dpi.h"

using namespace boost::interprocess;

class SharedPacketInformation
{
public:
    SharedPacketInformation();
    ~SharedPacketInformation();
    static size_t getSharedDataSize();
    interprocess_semaphore writer_, reader_;
    char sharedData_[1000];
    // Dpi* sharedData_;
private:
};

#endif

