#ifndef TIME_RECORDER_H_
#define TIME_RECORDER_H_

#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

enum RecorderType {
    NORMAL = 0,
    WRITER = 1,
    READER = 2,
};

class TimeRecorder
{
public:
    TimeRecorder();
    ~TimeRecorder();

    void write();
private:
    std::ofstream ofs;
    unsigned int dataSize_;
    RecorderType type_;
    std::vector <struct timespec> startTimes;
    std::vector <struct timespec> endTimes;
};

#endif

