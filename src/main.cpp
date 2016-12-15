#include <string>
#include <iostream>
#include <thread>

#include "unix_socket.h"
#include "door_api_manager.h"
#include "worker.h"

#include "shared_memory.h"
#include "shared_key.h"
#include "dpi.h"

int
main() {
    /*
    // check main thread 
    std::cout << "main" << std::this_thread::get_id() << std::endl;

    // initialize socket & server instance
    UnixSocket socket = UnixSocket();
    DoorApiManager doorApiManager = DoorApiManager();

    socket.subscribe(&doorApiManager);

    // start server
    socket.run();
    */

    /*
    std::string key = "hoge";
    char sharedData[16] = "hogehoge";
    SharedMemory<char, SharedKey>* sharedKeyMemory1 = new SharedMemory<char, SharedKey>(key);
    //sharedKeyMemory1->write(sharedData);
    char* hoge = NULL;
    sharedKeyMemory1->read(&hoge);
    std::cout << hoge << std::endl;

    /*
    std::string key = "hoge";
    char data[1000] = "hoge";
    char ipdata[10] = "hoge";
    Dpi* dpi = new Dpi(1, ipdata, ipdata, 2, 3, data);
    std::cout << sizeof(Dpi) << std::endl;
    // std::cout << sizeof(*dpi) << std::endl;
    SharedMemory<Dpi, SharedPacketInformation>* sharedKeyMemory2 = new SharedMemory<Dpi, SharedPacketInformation>(key);
    // sharedKeyMemory2->write(dpi);
    Dpi* dpi2=NULL;
     sharedKeyMemory2->read(&dpi2);
    //std::cout << dpi2->dstPort_ << std::endl;
    delete dpi;
    free(dpi2);
    */

    std::string key = "hoge";
    char sharedData[1000] = "hogehogehohogehoge";
    SharedMemory<char, SharedPacketInformation>* sharedKeyMemory1 = new SharedMemory<char, SharedPacketInformation>(key);
    // sharedKeyMemory1->write(sharedData);
    char* hoge = NULL;
    sharedKeyMemory1->read(&hoge);
    std::cout << hoge << std::endl;

    return 0;
}
