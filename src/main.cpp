#include <string>
#include <iostream>
#include "cpptoml.h"

using namespace std;

int
main() {
    // auto config = cpptoml::parse_file("../config.toml");
    // auto vals = config->get_qualified_array_of<std::string>("app.shm_key");

    // for (const auto& val  : *vals)
    // {
    //    cout << val << endl;
    // };
    
    // open socket
    UnixServer server = UnixServer();
    server.run();

    // start server



    return 0;
}
