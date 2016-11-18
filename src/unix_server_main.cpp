#include "cpptoml.h"
#include <string>
#include <iostream>

using namespace std;

int
main() {
    auto config = cpptoml::parse_file("config.toml");
    auto vals = config->get_qualified_array_of<std::string>("app.shm_key");

    for (const auto& val  : *vals)
    {
        cout << val << endl;
    };

    // UnixServer server = UnixServer();
    // server.run();

    return 0;
}
