#include "shared_key.h"

SharedKey::SharedKey(): writer_(1), reader_(0) {
    std::cout << "shared_key started" << std::endl;
}

SharedKey::~SharedKey() {
}

size_t
SharedKey::getSharedDataSize() {
    return sizeof(sharedData_);
}

void
SharedKey::writeDataToShm(char* key) {
    strcpy(sharedData_, key);
}

void
SharedKey::readDataFromShm(char* key) {
    memcpy(key, sharedData_, getSharedDataSize());
}
