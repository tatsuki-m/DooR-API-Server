#include <string>
#include <iostream>

#include "door_api_manager.h"
#include "unix_socket.h"

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

    // initialize socket & server instance
    UnixSocket socket = UnixSocket(socketName);
    DoorApiManager doorApiManager = DoorApiManager();

    socket.subscribe(&doorApiManager);

    // start server
    socket.run();

    return 0;
}
