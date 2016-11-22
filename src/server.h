#ifndef INCLUDED_SERVER
#define INCLUDED_SERVER

#include "i_observer.h"

class Server : public IObserver
{
public:
    Server();
    ~Server();

    void update(int);

private:
    int shmKey_;
};

#endif
