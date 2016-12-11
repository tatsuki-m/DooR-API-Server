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
    interprocess_semaphore writer_, reader_;
    char sharedData_[16];

private:
};
#endif

