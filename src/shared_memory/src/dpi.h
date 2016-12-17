#ifndef DPI_H_
#define DPI_H_

#include <iostream>
#include <cstring>
#include <time.h>

class Dpi
{

public:
    Dpi();
    Dpi(unsigned int id, char* srcIp, char* dstIp, unsigned int srcPort, unsigned int dstPort, char* data);
    ~Dpi();

// private:
    unsigned int id_;
    // using timestamp
    // struct tm timestamp_;
    char srcIp_[10];
    char dstIp_[10];
    unsigned int srcPort_;
    unsigned int dstPort_;
    char data_[1000];
};

#endif  //DPI_H_

