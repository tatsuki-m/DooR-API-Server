#include "time_recorder.h"

std::string BASE_FILE_DIR = "/tmp/recorder/";

TimeRecorder::TimeRecorder(std::string fileName) {
    fileName = BASE_FILE_DIR + fileName;
    ofs.open(fileName.c_str());
}

TimeRecorder::TimeRecorder(RecorderType recorderType, unsigned long dataSize) {
    std::string type;
    switch (recorderType) {
        case NORMAL:
          type = "normal";
          break;
        case WRITER:
          type = "writer";
          break;
        case READER:
          type = "reader";
          break;
        default:
          type = "other";
          break;
    }
    std::string fileName = BASE_FILE_DIR + "docker_" + std::to_string(dataSize) + "_" + type + ".csv";
    ofs.open(fileName.c_str());
}

TimeRecorder::~TimeRecorder() {
}

void
TimeRecorder::pushStartTime() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    startTimes.push_back(time);
}

void
TimeRecorder::pushEndTime() {
    struct timespec time;
    clock_gettime(CLOCK_MONOTONIC, &time);
    endTimes.push_back(time);
}

void
TimeRecorder::record() {
    ofs << "start_time, end_time, interval" << std::endl;
    for(unsigned long i = 0; i != startTimes.size(); ++i) {
        ofs << std::setfill('0') << std::setw(6) << std::right << (startTimes[i].tv_nsec) << ",";
        ofs << std::setfill('0') << std::setw(6) << (endTimes[i].tv_nsec) << ",";
        ofs << (endTimes[i].tv_nsec) - (startTimes[i].tv_nsec) << std::endl;
    };

}

