#include "shared_packet_information.h"

// writer is initialzer to write data to shm
SharedPacketInformation::SharedPacketInformation(): writer_(1), reader_(0) {
};

SharedPacketInformation::~SharedPacketInformation() {
}

size_t
SharedPacketInformation::getSharedDataSize() {
    return sizeof(Dpi);
}

void
SharedPacketInformation::writeDataToShm(Dpi* data) {
    sharedData_.id_ = data->id_;
    sharedData_.srcPort_ = data->srcPort_;
    sharedData_.dstPort_ = data->dstPort_;
}

void
SharedPacketInformation::readDataFromShm(Dpi* readData) {
    readData->id_ = sharedData_.id_;
    readData->srcPort_ = sharedData_.srcPort_;
    readData->dstPort_ = sharedData_.dstPort_;
}

