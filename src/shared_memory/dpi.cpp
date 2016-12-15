#include "dpi.h"

Dpi::Dpi() {
}


Dpi::Dpi(unsigned int id, char* srcIp, char* dstIp, unsigned int srcPort, unsigned int dstPort, char* data) {
    id_ = id;
    strcpy(srcIp_, srcIp_);
    strcpy(dstIp_, dstIp_);
    srcPort_ = srcPort;
    dstPort_ = dstPort;
    strcpy(data_, data);
}

Dpi::~Dpi() {
}

