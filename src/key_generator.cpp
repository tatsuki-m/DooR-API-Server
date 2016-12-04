#include "key_generator.h"

KeyGenerator::KeyGenerator() {
}

KeyGenerator::~KeyGenerator() {
}

// shmKeyname: hoge, key: 1 -> Generate Key: hoge01
std::string
KeyGenerator::createKey(char* baseKey, unsigned int key) {
    std::ostringstream sout;
    sout << std::setfill('0') << std::setw(2) << key;
    std::string appShmKey = baseKey + sout.str();
    return appShmKey;
}

