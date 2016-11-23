#ifndef DOOR_API_MANAGER_H_
#define DOOR_API_MANAGER_H_

#include <iostream>
#include <string>
#include <stdio.h>

#include "i_observer.h"
#include "door_api_worker.h"

class DoorApiManager : public IObserver
{
public:
    DoorApiManager();
    ~DoorApiManager();
    void create(int);

private:
    std::string getShmKey(int);
    void init();
    int shmKey_;
};

#endif
