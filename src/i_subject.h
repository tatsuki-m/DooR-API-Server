#ifndef SERVER_H_
#include "door_api_manager.h"
#endif

class ISubject
{
public:
    ISubject();
    virtual ~ISubject();
    virtual void subscribe(DoorApiManager* server);
    virtual void unsubscribe();
    virtual void notify(int);

private:
    DoorApiManager* doorApiManager_;
};

