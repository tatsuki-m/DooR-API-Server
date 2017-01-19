#include "sync_semaphore.h"

const int ERR = -1;

SyncSemaphore::SyncSemaphore() {
    std::cout << "constructor called" << std::endl;
}

SyncSemaphore::~SyncSemaphore() {
    std::cout << "destructor called" << std::endl;
}

void
SyncSemaphore::create(std::string semKey) {
    std::cout << "SyncSemaphore::create" << std::endl;
    semKey_ = semKey;
    try {
        if ((sem = sem_open(semKey_.c_str(), O_CREAT, 0660, 0)) == SEM_FAILED)
          throw;
    } catch(...) {
        std::cerr << "sem_open: ";
    }
}

void
SyncSemaphore::open(std::string semKey) {
    std::cout << "SyncSemaphore::open" << std::endl;
    semKey_ = semKey;
    try {
        if ((sem = sem_open(semKey_.c_str(), 0, 0, 0)) == SEM_FAILED)
          throw;
    } catch(...) {
        std::cerr << "sem_open: ";
    }
}

void
SyncSemaphore::wait() {
    std::cout << "SyncSemaphore::wait" << std::endl;
    try {
        if (sem_wait(sem) == ERR)
            throw;
    } catch(...) {
        std::cerr << "sem_wait: ";
    }
}

void
SyncSemaphore::post() {
    std::cout << "SyncSemaphore::post" << std::endl;
    try {
        if (sem_post(sem) == ERR)
            throw;
    } catch(...) {
        std::cerr << "sem_wait: ";
    }
}

void
SyncSemaphore::close() {
    std::cout << "SyncSemaphore::close" << std::endl;
    sem_close(sem);
    sem_unlink(semKey_.c_str());
}

