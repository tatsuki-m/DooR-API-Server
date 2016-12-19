#include "shared_key.h"

SharedKey::SharedKey(): writer_(1), reader_(0) {
    std::cout << "shared_key started" << std::endl;
}

SharedKey::~SharedKey() {
    delete[] sharedData_;
}

size_t
SharedKey::getSharedDataSize() {
    return sizeof(sharedData_);
}

