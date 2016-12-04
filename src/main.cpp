#include <string>
#include <iostream>
#include <thread>

#include "unix_socket.h"
#include "door_api_manager.h"
#include "worker.h"

int
main() {
    // auto config = cpptoml::parse_file("../config.toml");
    // auto vals = config->get_qualified_array_of<std::string>("app.shm_key");

    // for (const auto& val  : *vals)
    // {
    //    cout << val << endl;
    // };
    // specify socket name
    std::string socketName = "/tmp/unix-socket";

    // check main thread 
    std::cout << "main" << std::this_thread::get_id() << std::endl;

    // initialize socket & server instance
    UnixSocket socket = UnixSocket(socketName);
    DoorApiManager doorApiManager = DoorApiManager();

    socket.subscribe(&doorApiManager);

    // start server
    std::thread th(&UnixSocket::run, socket);
    th.join();
    
    /*j
    Worker* a, b, c;

    while (true) {
         std::cout << "main: " << std::this_thread::get_id() << std::endl;
         sleep(1);
    }
    */

    return 0;
}
