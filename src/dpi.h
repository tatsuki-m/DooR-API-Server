#ifndef DPI_H_
#define DPI_H_

#include <iostream>
#include <string>
#include <time.h>

class Dpi
{

public:
    Dpi();
    ~Dpi();

private:
    unsigned int id_;
    // using timestamp
    // struct tm timestamp_;
    std::string srcIp_;
    std::string dstIp_;
    unsigned int srcPort_;
    unsigned int dstPort_;
    char data[1000];
};

#endif  //DPI_H_

