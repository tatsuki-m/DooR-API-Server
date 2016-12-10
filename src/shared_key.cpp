#include "shared_key.h"

SharedKey::SharedKey(): writer_(1), reader_(0) {
    std::cout << "shared key" << std::endl;
}

SharedKey::~SharedKey() {
}


char*
SharedKey::getSharedData() {
    return sharedData_;
}

