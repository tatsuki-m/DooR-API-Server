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
//
std::string
KeyGenerator::createDoorShmKey(std::string baseKey, unsigned int workerID, unsigned int coutner) {
    std::ostringStream sout1, sout2;
    sout1 << std::setfill('0') << std::setw(2) << workerID;
    sout2 << std::setfill('0') << std::setw(2) << counter;
    std::string doorShmKey = baseKey + sout1.str() + sout2.str();
    return doorShmKey;
}



std::string
KeyGenerator::createSocketName(std::string baseKey, unsigned int key) {
    std::string socketName = baseKey + std::to_string(key);
    return socketName;
}


