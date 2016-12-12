#include "shared_packet_information.h"

SharedPacketInformation::SharedPacketInformation(): writer_(1), reader_(0) {
    std::cout << "shared packet information" << std::endl;
};

SharedPacketInformation::~SharedPacketInformation() {
}

size_t
SharedPacketInformation::getSharedDataSize() {
    return sizeof(Dpi);
}

