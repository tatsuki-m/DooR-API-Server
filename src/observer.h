#include <cstddef>

#include "class.h"

class IObserver
{
public:
    virtual ~IObserver();
    virtual void update(int);
    void setObject(ISubject* pSubject);

protected:
    ISubject* p_Socket_;
};

class ISubject
{
public:
    ISubject();
    virtual ~ISubject();
    virtual void subscribe(IObserver* pObserver);
    virtual void unsubscribe();
    virtual void notify(int);

private:
    IObserver* p_Observer_;
};

