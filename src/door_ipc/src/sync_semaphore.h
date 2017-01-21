#ifndef SYNC_SEMAPHORE_H_
#define SYNC_SEMAPHORE_H_

#include <unistd.h>
#include <string>
#include <iostream>
#include <semaphore.h>
#include <fcntl.h>    /* For O_RDWR */

class SyncSemaphore {
public:
    SyncSemaphore();
    ~SyncSemaphore();

    void wait();
    void post();
    void close();
    void create(std::string);
    void open(std::string);
    int getValue();
private:
    std::string semKey_;
    sem_t *sem;
};

#endif

