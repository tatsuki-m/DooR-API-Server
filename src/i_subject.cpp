#include <cstddef>
#include "i_subject.h"

ISubject::ISubject() {
}

ISubject::~ISubject() {
    // delegate destructor to unscribe method
}

void
ISubject::subscribe(Server* server) {
    server_ = server;
}

void
ISubject::unsubscribe(Server* server) {
    server_ = NULL;
}

void
ISubject::notify(int num) {
    (server_)->update(num);
}

