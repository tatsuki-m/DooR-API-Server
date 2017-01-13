#ifndef TIME_RECORDER_H_
#define TIME_RECORDER_H_

#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <iomanip>

enum RecorderType {
    NORMAL = 0,
    WRITER = 1,
    READER = 2,
};

class TimeRecorder
{

public:
    TimeRecorder(std::string);
    TimeRecorder(RecorderType, unsigned long);
    ~TimeRecorder();
    void record();
    void pushStartTime();
    void pushEndTime();
    void write();
private:
    std::ofstream ofs;
    std::vector<struct timespec> startTimes;
    std::vector<struct timespec> endTimes;
};

#endif

