#ifndef KEY_GENERATOR_H_
#define KEY_GENERATOR_H_

#include <iostream>
#include <cstring>
#include <string>
#include <sstream> /* ostringstream */
#include <iomanip> /* setfill, setw */

class KeyGenerator
{
public:
    KeyGenerator();
    ~KeyGenerator();
    static std::string createDoorShmKey(std::string, unsigned int, unsigned int);
    static std::string createSocketName(std::string, unsigned int);
};

#endif

