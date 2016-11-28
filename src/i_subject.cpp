#ifndef I_SUBJECT_H_
#define I_SUBJECT_H_

#include "i_subject.h"

ISubject::ISubject() {
}

ISubject::~ISubject() {
    // delegate destructor to unscribe method
}

void
ISubject::subscribe(DoorApiManager* manager) {
    doorApiManager_ = manager;
}

void
ISubject::unsubscribe() {
    doorApiManager_ = NULL;
}

void
ISubject::notify(std::string shmKey) {
    (doorApiManager_)->create(shmKey);
}

#endif
