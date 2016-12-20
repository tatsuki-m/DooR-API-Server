#include "key_generator.h"

KeyGenerator::KeyGenerator() {
}

KeyGenerator::~KeyGenerator() {
}

// name: hoge, key: 1 -> Generate Key: hoge01
//std::string
//KeyGenerator::createSocketName(std::string baseKey, unsigned int key) {
//    std::ostringstream sout;
//    sout << std::setfill('0') << std::setw(2) << key;
//    std::string appShmKey = baseKey + sout.str();
//    return appShmKey;
//}


std::string
KeyGenerator::createSocketName(std::string baseKey, unsigned int key) {
    std::string socketName = baseKey + std::to_string(key);
    return socketName;
}


