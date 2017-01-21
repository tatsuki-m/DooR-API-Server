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
#include "door_api/door_api.h"

void
signalHandler(int sigNum) {
    std::cout << "Interrupt signal (" << sigNum << ") received." << std::endl;

    std::cout << "unlink fd....." <<std::endl;
    std::string socketName = "/tmp/unix-socket/unix-socket";
    unlink(socketName.c_str());
    //system("exec rm  /tmp/unix-socket/*");

    std::cout << "delete shm" << std::endl;
    //system("exec rm  /dev/shm/ShmKey*");
    //system("exec rm  /dev/shm/sem.*");

    std::cout << "Going to sleep.." <<std::endl;
    exit(sigNum);
}

int
main() {
    signal(SIGINT, signalHandler);

   std::string socketName = "/tmp/unix-socket/unix-socket";
    // initialize socket & server instance
    UnixDomainSocketServer socket = UnixDomainSocketServer(socketName);
    DoorApiManager doorApiManager = DoorApiManager();
    socket.subscribe(&doorApiManager);
    // start server
    socket.run();
/*
    SyncSemaphore sem;
    sem.open("hoge");
    sem.post();
*/

/*
    std::string shmKey = "hoge";
    SharedMemory<Dpi, SharedPacketInformation> doorShm = SharedMemory<Dpi, SharedPacketInformation>(shmKey);
    Dpi* dpi = NULL;
    doorShm.read(&dpi);
    std::cout << dpi->data_ << std::endl;

    delete dpi;
*/

    return 0;
}
