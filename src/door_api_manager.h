#ifndef DOOR_API_MANAGER_H_
#define DOOR_API_MANAGER_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>
#include <thread>
#include <algorithm>

#include "i_observer.h"
#include "door_api_worker.h"
#include "door_unix_domain_socket_client/socket_ack.h"
#include "door_unix_domain_socket_client/unix_domain_socket_client.h"

class DoorApiManager : public IObserver
{
public:
    DoorApiManager();
    ~DoorApiManager();
    void create(std::string);
    bool destroy(unsigned int);

    // for using DoorApiWoker in map
    bool operator()(const DoorApiWorker &lWorker, const DoorApiWorker &rWorker) { return lWorker.id_ < rWorker.id_; }
private:
    //std::vector<DoorApiWorker*> doorApiWorkers;
    std::map<unsigned int, DoorApiWorker*> workerMap;
    unsigned int workerId_;
};

#endif

