#include <string>
#include <iostream>
#include <thread>

#include "unix_socket.h"
#include "door_api_manager.h"
#include "worker.h"

#include "door_shared_memory/shared_key.h"
#include "door_shared_memory/shared_memory.h"
#include "door_shared_memory/shared_packet_information.h"
#include "door_shared_memory/dpi.h"


int
main() {
    // check main thread 
    std::cout << "main" << std::this_thread::get_id() << std::endl;
/*
    // initialize socket & server instance
    UnixSocket socket = UnixSocket();
    DoorApiManager doorApiManager = DoorApiManager();
    socket.subscribe(&doorApiManager);

    // start server
    socket.run();
*/

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
//    sharedKeyMemory1->write(sharedData);
    char* hoge = NULL;
    sharedKeyMemory1->read(&hoge);
    std::cout << hoge << std::endl;
*/

    std::string key = "hoge";
    //char data[1000] = "hoge";
    //char ipdata[10] = "hoge";
    //Dpi* dpi = new Dpi(1, ipdata, ipdata, 2, 3, data);
    unsigned int id = 1;
    unsigned int srcPort = 1;
    unsigned int dstPort = 1;
    Dpi* dpi = new Dpi(id,srcPort, dstPort);
    std::cout << sizeof(Dpi) << std::endl;
    // std::cout << sizeof(*dpi) << std::endl;
    SharedMemory<Dpi, SharedPacketInformation>* sharedKeyMemory2 = new SharedMemory<Dpi, SharedPacketInformation>(key);
    // sharedKeyMemory2->write(dpi);
    Dpi* dpi2=NULL;
    sharedKeyMemory2->read(&dpi2);
    std::cout << dpi2->dstPort_ << std::endl;
    delete dpi;
    delete dpi2;

/*
    std::string key = "hoge";
    char sharedData[1000] = "hogehogehohogehoge";
    SharedMemory<char, SharedPacketInformation>* sharedKeyMemory1 = new SharedMemory<char, SharedPacketInformation>(key);
    //sharedKeyMemory2->write(sharedData);
    char* hoge = NULL;
    sharedKeyMemory1->read(&hoge);
    std::cout << hoge << std::endl;
*/


    return 0;
}
