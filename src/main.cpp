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
    Worker* a, b, c;

    while (true) {
         std::cout << "main: " << std::this_thread::get_id() << std::endl;
         sleep(1);
    }
    */

    return 0;
}
