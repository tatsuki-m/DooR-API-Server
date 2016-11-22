#include "server.h"

Server::Server() {
    shmKey_ = 0;
}

Server::~Server() {
}

void
Server::update(int num) {
    shmKey_ = num;
}

