#include <string>
#include <iostream>
#include <thread>

#include "door_api_manager.h"
#include "unix_domain_socket_server.h"

#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/dpi.h"
#include "door_api/door_api.h"

int
main() {
    std::cout << "main" << std::this_thread::get_id() << std::endl;
/*
    DoorApi doorApi = DoorApi();
    doorApi.getAllInformation("hoge", "hoge");
*/

    // initialize socket & server instance
    UnixDomainSocketServer socket = UnixDomainSocketServer();
    DoorApiManager doorApiManager = DoorApiManager();
    socket.subscribe(&doorApiManager);

    // start server
    socket.run();

/*
    std::string key = "hoge";
    char data[10] = "hoge";
    Key* key = new Key(data);
    SharedMemory<Key, SharedKey>* sharedKey= new SharedMemory<Key, SharedKey>(key);
    sharedKey
*/

/*
    std::string key = "hoge";
    char sharedData[16] = "hogehoge";
    SharedMemory<char, SharedKey>* sharedKeyMemory1 = new SharedMemory<char, SharedKey>(key);
   // sharedKeyMemory1->write(sharedData);
    char* hoge = NULL;
    sharedKeyMemory1->read(&hoge);
    std::cout << hoge << std::endl;

    //delete[] sharedData;
    //delete sharedKeyMemory1;
*/
/*
    std::string key = "hoge";
    //char data[1000] = "hoge";
    //char ipdata[10] = "hoge";
    //Dpi* dpi = new Dpi(1, ipdata, ipdata, 2, 3, data);
    //
/*
    SharedMemory<Dpi, SharedPacketInformation>* sharedKeyMemory2 = new SharedMemory<Dpi, SharedPacketInformation>(key);
    Dpi* dpi2=NULL;
    sharedKeyMemory2->read(&dpi2);
    std::cout << dpi2->dstPort_ << std::endl;
    delete dpi2;
*/

/*
    unsigned int id = 1;
    unsigned int srcPort = 1;
    unsigned int dstPort = 1;
    Dpi* dpi = new Dpi(id, srcPort, dstPort);
    std::cout << sizeof(Dpi) << std::endl;
    // std::cout << sizeof(*dpi) << std::endl;
    SharedMemory<Dpi, SharedPacketInformation>* sharedKeyMemory2 = new SharedMemory<Dpi, SharedPacketInformation>(key);
    sharedKeyMemory2->write(dpi);
    delete dpi;
*/

    return 0;
}
