#ifndef I_SUBJECT_H_
#define I_SUBJECT_H_

#include "i_subject.h"

ISubject::ISubject() {
}

ISubject::~ISubject() {
    // delegate destructor to unscribe method
    unsubscribe();
}

void
ISubject::subscribe(DoorApiManager* manager) {
    doorApiManager_ = manager;
}

void
ISubject::unsubscribe() {
    delete doorApiManager_;
}

void
ISubject::notifyCreate(std::string socketName) {
    (doorApiManager_)->create(socketName);
}

bool
ISubject::notifyDestroy(unsigned int workerId) {
    return (doorApiManager_)->destroy(workerId);
}

#endif

