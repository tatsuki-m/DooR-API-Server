#ifndef DPI_H_
#define DPI_H_

#include <iostream>
#include <cstring>
#include <time.h>

class Dpi
{

public:
    Dpi();
    Dpi(unsigned int id, unsigned int srcPort, unsigned int dstPort);
    //Dpi(unsigned int id, char* srcIp, char* dstIp, unsigned int srcPort, unsigned int dstPort, char* data);
    ~Dpi();

// private:
    unsigned int id_;
    // using timestamp
    // struct tm timestamp_;
    //char srcIp_[64];
    //char dstIp_[64];
    unsigned int srcPort_;
    unsigned int dstPort_;
    //char data_[256];
};

#endif  //DPI_H_

