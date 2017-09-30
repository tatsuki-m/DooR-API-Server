#include "mmap_ring.h"

MmapRing::MmapRing(std::string dataFileName, std::string controlFileName) 
{
    dataFileName_ = dataFileName;
    controlFileName_ = controlFileName;
}

MmapRing::~MmapRing() 
{
}

void
MmapRing::masterInit()
{
    initFile();
    initMmap();
    initBuffer();
    for(int i=0; i<no_of_buffers; i++) CB_init(cb_master_[i]);
    std::cout << "cb_master assignment completed" << std::endl;
}

void
MmapRing::slaveInit()
{
    initMmap();
    initMmap();
    initBuffer();
}

// initialize Mmap
void
MmapRing::initMmap()
{
    // filehandler for data/control file
    struct stat sb_control;
    int fd, fd_process_control;

    fd=open (dataFileName_.c_str(), O_RDWR);
    fd_process_control = open(controlFileName_.c_str(), O_RDWR);
    try {
        if (fd == -1) {
            std::cerr << "dataFile open"<< std::endl;
            throw;
        }
        if (fstat(fd, &sb_) == -1) {
            std::cerr << "fstat" << std::endl;
            throw;
        }
        if (fstat(fd_process_control, &sb_control) == -1) {
            std::cerr << "fstat fd_process_control" << std::endl;
            throw;
        }
        if (!S_ISREG(sb_.st_mode)) {
            std::cerr << dataFileName_ << " is not a file" << std::endl;
            throw;
        }
    } catch(...) {
      // error
    }

    //initialize mmpas for shared memory
    p_ = static_cast<char*>( mmap((caddr_t)0, sb_.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0) );
    p_control_ = static_cast<char*>( mmap((caddr_t)0, sb_control.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_process_control, 0) );

    try{
        if (p_==MAP_FAILED) {
            std::cerr << "mmap" << std::endl;
            throw;
        }
        if (p_control_==MAP_FAILED) {
            std::cerr << "mmap p_control" << std::endl;
            throw;
        }
        if ( (close(fd)==-1) && (close(fd_process_control==-1)) ) {
            std::cerr << "close" << std::endl;
            throw;
        }
    } catch(...) {
        // error
    }
}

void 
MmapRing::initFile()
{
    // resize file to allocate memory size
    int fileSize = (no_of_buffers+1) * sizeof(circular_buffer);
    FILE *fp = fopen(dataFileName_.c_str(), "w");

    //truncate file to the required data size
    fseek(fp, fileSize, SEEK_SET);
    fputc('\0', fp);
    fclose(fp);
}

void
MmapRing::initBuffer()
{
    // cb_master_; store pointers of circular_buffer
    cb_master_ = (circular_buffer **)malloc(no_of_buffers*sizeof(circular_buffer *));
    for (int i=0; i<no_of_buffers; i++) {
        cb_master_[i] = (circular_buffer *)(p_+i*sizeof(circular_buffer) );
    }
    std::cout << "cb_master assignment complete" << std::endl;
}

///////////////////////////////////////////////////////////////
// send control message stating the mmpas are initialized
// p_control_[0]: control process wait-read-stop
// 0x0: master-wait
// 0x1: slave-read
// 0x2: master-stop the process
// 0x3: slave-stop the process
// p_control_[1]: control master-process waiting for slave-process
// 0x0: master-keep wating
// 0x1: master-stop waiting
///////////////////////////////////////////////////////////////
bool
MmapRing::push(std::string sharedData)
{
    const char* c_sharedData = sharedData.c_str();
    std::cout << "Circular Buffer initialized" << std::endl;
    bool cb_push_passed = true;
    int whileLoop =0;
    std::string testData = "/001/002/003/004/005/006/007/008/009/010/011/012/013/014/015";
    cb_buffer_struct push_data;
    int divided_num = (int)ceil(testData.size()/sizeof(push_data.buffer));

    // send control message stating the mmaps are initialized
    p_control_[0] = 0x0;
    while( p_control_[0] == 0x0) {
        continue;
    }

    // 
    while( p_control_[0] == 0x1 && whileLoop < loop_count ) {
        int i;
        for (i=0; i < no_of_buffers; i++) {
            int start_num = ((whileLoop+i)%divided_num)*sizeof(push_data.buffer);
            std::string data =testData.substr(start_num, 4);
            std::cout << "data: " << data << std::endl;
            strcpy( push_data.buffer, data.c_str());
            cb_push_passed  = (CB_push(cb_master_[i], push_data) == 1) ? true : false;
        }

        if (!cb_push_passed) {
            return true;
        }

        p_control_[1] = 0x0;
        while(p_control_[1] == 0x0 && whileLoop < loop_count)
            continue;

        whileLoop++;
    }

    // stop the process using shared memory control bit
    p_control_[0] = 0x2;

    // unmap
    if (munmap(p_, sb_.st_size) == -1) {
        std::cerr << "munmap" << std::endl;
        return true;
    }

    return false;
}

bool
MmapRing::pop()
{
    int whileLoop=0;
    cb_buffer_struct pull_data;

    p_control_[0] = 0x1;
    while(p_control_[0] == 0x1 && whileLoop < loop_count) {
        p_control_[1] = 0x1;


        //pull buffer data
        int i;
        for(i=0; i<no_of_buffers; i++) {
            int buf_empty;
            pull_data = CB_pop(cb_master_[i], &buf_empty);
            if (whileLoop % 1 == 0 && buf_empty == 0) {
                printf("cb_master %d %s %llu %llu %llu\n", i, pull_data.buffer, cb_master_[i]->read_offset, cb_master_[i]->write_offset, cb_master_[i]->count, cb_master_[i]->size);
            }
        }
    }
    p_control_[0] = 0x3;
    return false;
}


