#ifndef I_OBSERVER_H_
#define I_OBSERVER_H_

#include <string>
#include <cstddef>

class IObserver
{
public:
    virtual ~IObserver();
    virtual void create(std::string);
    virtual bool destroy(unsigned int);
};

#endif

