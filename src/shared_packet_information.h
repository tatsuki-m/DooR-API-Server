#ifndef SHARED_PACKET_INFORMATION_H_
#define SHARED_PACKET_INFORMATION_H_

#include <iostream>
#include <string>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using namespace boost::interprocess;

class SharedPacketInformation
{
public:
    SharedPacketInformation();
    ~SharedPacketInformation();

private:
    interprocess_semaphore writer_, reader_;
    char doorData_[100];
};

#endif

