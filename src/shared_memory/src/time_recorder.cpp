#include "time_recorder.h"

std::string BASE_FILE_DIR = "/tmp/recorder/"

TimeRecorder::TimeRecorder(std::string filename) {
    type_ = NORMAL;
    dataSize_ = 0;
    filename_ = BASE_FILE_DIR + filename;
    std::ofstream ofs(filename_.c_str)
}

TimeRecorder::TimeRecorder(RecordType type, unsigned int dataSize) {
    type_ = type;
    dataSize_ = dataSize;
    filename_ = BASE_FILE_DIR + "test_" + 
}

TimeRecorder::~TimeRecorder() {
}

