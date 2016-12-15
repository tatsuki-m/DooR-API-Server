#include "shared_packet_information.h"

SharedPacketInformation::SharedPacketInformation(): writer_(1), reader_(0) {
    // sharedData_ = new Dpi();
};

SharedPacketInformation::~SharedPacketInformation() {
    delete sharedData_;
}

size_t
SharedPacketInformation::getSharedDataSize() {
    return sizeof(sharedData_);
    // return sizeof(Dpi);
}

