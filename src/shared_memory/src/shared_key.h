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
    static size_t getSharedDataSize();
    void writeDataToShm(char*);
    void readDataFromShm(char*);
    interprocess_semaphore writer_, reader_;
    char sharedData_[64];
private:
};
#endif

