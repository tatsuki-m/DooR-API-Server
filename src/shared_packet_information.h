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
    interprocess_semaphore writer_, reader_;
    Dpi* sharedData_;
private:
};

#endif

