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
    //std::cout << "main" << std::this_thread::get_id() << std::endl;
    std::string shmKey = "hoge";
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    std::cout << "DoorWorker::run" << std::endl;
    //Dpi dpi = Dpi(id, srcPort, dstPort);
    Dpi dpi = Dpi();
    std::cout << sizeof(dpi.data_) <<  std::endl;
    for (int i=0; i < sizeof(dpi.data_); i++) {
        dpi.data_[i]= 'a';
    }

    std::cout << "DoorWorker::run start writing" << std::endl;
    doorShm.write(&dpi);


/*
    // initialize socket & server instance
    UnixDomainSocketServer socket = UnixDomainSocketServer();
    DoorApiManager doorApiManager = DoorApiManager();
    socket.subscribe(&doorApiManager);

    // start server
    socket.run();
*/

/*
    std::string shmKey = "hoge";
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    std::cout << "DoorWorker::run" << std::endl;
    unsigned int id = 100000;
    unsigned int srcPort = 10000;
    unsigned int dstPort = 10000;
    Dpi dpi = Dpi(id, srcPort, dstPort);
    std::cout << "DoorWorker::run start writing" << std::endl;
    doorShm.write(&dpi);
*/
    /*
    std::string shmKey = "hogehoge";
    SharedMemory<char, SharedKey>* sharedKeyMemory1 = new SharedMemory<char, SharedKey>(shmKey);
    char* hoge = NULL;
    sharedKeyMemory1->read(&hoge);
    std::cout << hoge << std::endl;
    delete hoge;
    return 0;
    */
}
