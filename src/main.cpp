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
    char sharedData[100] = "hoge";
    SharedMemory<char, SharedKey>* sharedKeyMemory1 = new SharedMemory<char, SharedKey>(key);
    sharedKeyMemory0->write(sharedData);
    char* hoge = NULL;
    sharedKeyMemory1->read(&hoge);
    std::cout << hoge << std::endl;
    */

    std::string key = "hoge";
    char data[1000] = "hoge";
    char ipdata[10] = "hoge";
    Dpi* dpi = new Dpi(1, ipdata, ipdata, 2, 3, data);
    std::cout << sizeof(Dpi) << std::endl;
    // std::cout << sizeof(*dpi) << std::endl;
    SharedMemory<Dpi, SharedPacketInformation>* sharedKeyMemory2 = new SharedMemory<Dpi, SharedPacketInformation>(key);
    // sharedKeyMemory2->write(dpi);
    Dpi* dpi2 = new Dpi;
    sharedKeyMemory2->read(&dpi);
    std::cout << dpi2->dstPort_ << std::endl;
    return 0;
}
