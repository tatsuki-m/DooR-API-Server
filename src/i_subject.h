//#ifdef I_SUBJECT_H_
//#define I_SUBJECT_H_

#include <string>
#include "door_api_manager.h"

class ISubject
{
public:
    ISubject();
    virtual ~ISubject();
    virtual void subscribe(DoorApiManager* server);
    virtual void unsubscribe();
    virtual void notifyCreate(std::string);
    virtual bool notifyDestroy(unsigned int);

private:
    DoorApiManager* doorApiManager_;
};

//#endif

