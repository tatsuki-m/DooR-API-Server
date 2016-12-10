#ifndef SHARED_KEY_H_
#define SHARED_KEY_H_

#include <iostream>
#include <string>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>

using namespace boost::interprocess;

class SharedKey
{
public:
    SharedKey();
    ~SharedKey();
    char* getSharedData();
    interprocess_semaphore writer_, reader_;

private:
    char sharedData_[16];
};
#endif

