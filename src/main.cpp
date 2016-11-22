#include <string>
#include <iostream>

#include "server.h"
#include "unix_socket.h"

int
main() {
    // auto config = cpptoml::parse_file("../config.toml");
    // auto vals = config->get_qualified_array_of<std::string>("app.shm_key");

    // for (const auto& val  : *vals)
    // {
    //    cout << val << endl;
    // };

    // initialize socket & server instance
    UnixSocket socket = UnixSocket();
    Server server = Server();

    socket.subscribe(&server);

    // start server
    socket.run();


    return 0;
}
