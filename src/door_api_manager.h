#ifndef DOOR_API_MANAGER_H_
#define DOOR_API_MANAGER_H_

#include <iostream>
#include <string>
#include <stdio.h>

#include "i_observer.h"
#include "worker.h"

class DoorApiManager : public IObserver
{
public:
    DoorApiManager();
    ~DoorApiManager();
    void create(int);

private:
    std::string getShmKey(int);
    int shmKey_;
};

#endif
