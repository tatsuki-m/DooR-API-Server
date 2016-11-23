#ifndef I_SUBJECT_H_
#define I_SUBJECT_H_

#include <cstddef>
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
ISubject::notify(int num) {
    (doorApiManager_)->create(num);
}

#endif