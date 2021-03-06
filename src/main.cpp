#include <string>
#include <iostream>
#include <thread>
#include <csignal>
#include <time.h>

#include "door_api_manager.h"
#include "unix_domain_socket_server.h"

#include "door_ipc/shared_memory.h"
#include "door_ipc/shared_packet_information.h"
#include "door_ipc/sync_semaphore.h"
#include "door_ipc/dpi.h"
#include "door_ipc/mmap_ring.h"
#include "door_api/door_api.h"

void
signalHandler(int sigNum) {
    std::cout << "Interrupt signal (" << sigNum << ") received." << std::endl;

    std::cout << "unlink fd....." <<std::endl;
    std::string socketName = "/tmp/unix-socket/init-socket";
    unlink(socketName.c_str());
    system("exec rm  /tmp/unix-socket/*");

    std::cout << "delete shm" << std::endl;
    system("exec rm  /dev/shm/ShmKey*");
    system("exec rm  /dev/shm/sem.*");

    std::cout << "Going to sleep.." <<std::endl;
    exit(sigNum);
}

int
main() {
    signal(SIGINT, signalHandler);
    /*
    std::string dataFileName = "/tmp/SharedMem";
    std::string controlFileName = "/tmp/SharedStatMem";

    MmapRing ring_buffer = MmapRing(dataFileName, controlFileName);
    ring_buffer.masterInit();
    char testData[64] = "aaa\0bbb\0ccc\0ddd\0eee\0ggg\0hhh\0iii\0kkk\0lll\0mmm\0nnn\0ooo\0qqq\0rrr";
    int length = sizeof(testData);
    //char * p = &(testData[0]);
    //std::cout << &p << std::endl;
    //std::cout << testData[0] << std::endl;
    //std::cout << &(testData[0]) << std::endl;
    ring_buffer.push((char *)testData, 64);
    */

    // initialize socket & server instance
    std::string socketName = "/tmp/unix-socket/init-socket";
    UnixDomainSocketServer socket = UnixDomainSocketServer(socketName);
    DoorApiManager doorApiManager = DoorApiManager();
    socket.subscribe(&doorApiManager);
    // start server
    socket.run();



/*
    std::string shmKey = "hoge";

    int counter = 0;
    struct timespec startTime, endTime;
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    clock_gettime(CLOCK_MONOTONIC, &startTime);
    while(counter<1000) {
        counter++;
    }
    clock_gettime(CLOCK_MONOTONIC, &endTime);
    std::string fileName = "hoge.csv";
    std::cout << fileName << std::endl;
    std::ofstream ofs(fileName.c_str(), std::ios::app);
    ofs << std::setfill('1') << std::setw(6) << startTime.tv_nsec << ",";
    ofs << std::setfill('0') << std::setw(6) << endTime.tv_nsec << ",";
    ofs << endTime.tv_nsec - startTime.tv_nsec << std::endl;
*/
    return 0;
}
