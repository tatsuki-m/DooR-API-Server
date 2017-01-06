#ifndef DOOR_API_MANAGER_H_
#define DOOR_API_MANAGER_H_

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <thread>

#include "i_observer.h"
#include "door_api_worker.h"

class DoorApiManager : public IObserver
{
public:
    DoorApiManager();
    ~DoorApiManager();
    void create(std::string);

private:
    unsigned int workerNum_;
    std::vector<DoorApiWorker*> doorApiWorkers;
};

#endif

