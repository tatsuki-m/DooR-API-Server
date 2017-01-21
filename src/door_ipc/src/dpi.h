#ifndef DPI_H_
#define DPI_H_

#include <iostream>
#include <cstring>
#include <time.h>

enum ConType {
    UNIX_DOMAIN = 1,
    TCP = 2,
};

class Dpi
{

public:
    Dpi();
   // Dpi(unsigned int id, unsigned int srcPort, unsigned int dstPort);
    //Dpi(unsigned int id, char* srcIp, char* dstIp, unsigned int srcPort, unsigned int dstPort, char* data);
    ~Dpi();

    char data_[1500];
// private:
    //unsigned int id_;
    //unsigned int srcPort_;
    //unsigned int dstPort_;
    // using timestamp
    // struct tm timestamp_;
    //char srcIp_[64];
    //char dstIp_[64];
};

#endif  //DPI_H_

