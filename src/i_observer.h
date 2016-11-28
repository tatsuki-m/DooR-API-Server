#ifndef I_OBSERVER__H_
#define I_OBSERVER_H_

#include <string>
#include <cstddef>

class IObserver
{
public:
    virtual ~IObserver();
    virtual void create(std::string);
};

#endif

