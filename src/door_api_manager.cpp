#include <iostream>
#include "door_api_manager.h"

DoorApiManager::DoorApiManager() {
    shmKey_ = 0;
}

DoorApiManager::~DoorApiManager() {
}

void
DoorApiManager::update(int num) {
    shmKey_ = num;
    std::cout << "data = " << num << std::endl;
}

