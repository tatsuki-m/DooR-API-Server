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

#include "door_unix_domain_socket_client/socket_ack.h"
#include "door_unix_domain_socket_client/unix_domain_socket_client.h"

class DoorApiWorker
{
public:
    DoorApiWorker(unsigned int, std::string);
    ~DoorApiWorker();
    void stopWorkerSocketServer();

    unsigned int id_;
    std::string socketName_;
private:
    void run(std::string);
    unsigned int instanceNum_ = 0;
    std::thread th_;
    //std::mutex mtx_;
    //std::condition_variable cv_;
};

#endif

