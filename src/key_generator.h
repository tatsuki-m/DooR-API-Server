#ifndef KEY_GENERATOR_H_
#define KEY_GENERATOR_H_

#include <iostream>
#include <string>
#include <sstream> /* ostringstream */
#include <iomanip> /* setfill, setw */

class KeyGenerator
{
public:
    KeyGenerator();
    ~KeyGenerator();
    static std::string createKey(char*, unsigned int);
};

#endif

