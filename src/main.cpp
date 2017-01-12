#include <string>
#include <iostream>
#include <thread>

#include "door_api_manager.h"
#include "unix_domain_socket_server.h"

#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/dpi.h"
#include "door_api/door_api.h"

int
main() {
    // initialize socket & server instance
    UnixDomainSocketServer socket = UnixDomainSocketServer();
    DoorApiManager doorApiManager = DoorApiManager();
    socket.subscribe(&doorApiManager);

    // start server
    socket.run();

/*
    //std::cout << "main" << std::this_thread::get_id() << std::endl;
    std::string shmKey = "hoge";
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    std::cout << "DoorWorker::run" << std::endl;
    Dpi dpi = Dpi();
    std::cout << sizeof(dpi.data_) <<  std::endl;
    for (int i=0; i < sizeof(dpi.data_); i++) {
        dpi.data_[i]= 'a';
    }

    std::cout << "DoorWorker::run start writing" << std::endl;
    doorShm.write(&dpi);
    doorShm.removeSharedMemory();

    return 0;
}
