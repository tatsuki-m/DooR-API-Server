#ifndef SERVER_H_
#include <string>

#include "door_api_manager.h"

class ISubject
{
public:
    ISubject();
    virtual ~ISubject();
    virtual void subscribe(DoorApiManager* server);
    virtual void unsubscribe();
    virtual void notify(std::string);

private:
    DoorApiManager* doorApiManager_;
};

#endif

