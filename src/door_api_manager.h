#ifndef INCLUDED_SERVER
#define INCLUDED_SERVER

#include <stdio.h>
#include "i_observer.h"

class DoorApiManager : public IObserver
{
public:
    DoorApiManager();
    ~DoorApiManager();

    void create(int);

private:
    int shmKey_;
};

#endif
