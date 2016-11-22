#ifndef INCLUDED_SERVER
#include "server.h"
#endif

class ISubject
{
public:
    ISubject();
    virtual ~ISubject();
    virtual void subscribe(Server* server);
    virtual void unsubscribe(Server* server);
    virtual void notify(int);

private:
    Server* server_;
};

