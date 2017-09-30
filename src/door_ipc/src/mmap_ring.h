#ifndef MMAP_RING_MASTER_H_
#define MMAP_RING_MASTER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>
#include <sys/mman.h>
#include <string>
#include <iostream>
#include <math.h>
#include "circular_buffer.h"

class MmapRing {
public:
    MmapRing(std::string, std::string);
    ~MmapRing();
    void masterInit();
    void slaveInit();
    bool push(std::string);
    bool pop();
private:
    void initFile();
    void initMmap();
    void initBuffer();

    // file handler for data/control file
    char *p_;
    char *p_control_;

    struct stat sb_;
    // circular buffer
    circular_buffer **cb_master_;

    // number of circular buffer
    const int no_of_buffers = 16;
    const int loop_count = 20/*2000*/;

    std::string controlFileName_;
    std::string dataFileName_;
};

#endif

