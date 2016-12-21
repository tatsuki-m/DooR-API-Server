#ifndef DOOR_API_WORKER_H_
#define DOOR_API_WORKER_H_

#include <iostream>
#include <string>
#include <thread>
//#include <mutex>
//#include <condition_variable>
//#include <chrono>

#include "key_generator.h"
#include "worker_unix_domain_socket_server.h"

class DoorApiWorker
{
public:
    DoorApiWorker(unsigned int, std::string);
    ~DoorApiWorker();
private:
    void run(std::string);
    std::string getAppShmKey();

    unsigned int id_;
    unsigned int instanceNum_;
    std::string socketName_;
    bool abort_;
    std::thread th_;
    //std::mutex mtx_;
    //std::condition_variable cv_;
};

#endif

