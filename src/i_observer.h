#ifndef INCLUDED_I_OBSERVER
#define INCLUDED_I_OBSERVER

class IObserver
{
public:
    virtual ~IObserver();
    virtual void update(int);

};

#endif

