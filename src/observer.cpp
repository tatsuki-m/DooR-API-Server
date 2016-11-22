#include "observer.h"

ISubject::ISubject() {
}

ISubject::~ISubject() {
    // delegate destructor to unscribe method
}

void
ISubject::subscribe(IObserver* pObserver) {
    pObserver->setObject(this);
}

void
ISubject::unsubscribe() {
    (p_Observer_)->setObject(NULL);
}

void
ISubject::notify(int num) {
    (p_Observer_)->update(num);
}


IObserver::~IObserver() {
}

void
IObserver::update(int num) {
}

void
IObserver::setObject(ISubject* pSubject) {
    p_Socket_ = pSubject;
}

