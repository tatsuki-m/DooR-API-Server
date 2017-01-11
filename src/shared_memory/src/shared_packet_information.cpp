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
    strcpy(sharedData_.data_, data->data_);
}

void
SharedPacketInformation::readDataFromShm(Dpi* readData) {
    strcpy(readData->data_, sharedData_.data_);
}

