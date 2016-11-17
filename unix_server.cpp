#include "unix_server.h"

const char* UnixServer::socket_name_ = "/tmp/unix-socket";

UnixServer::UnixServer() {
    //register_handler();
    unlink(socket_name_);
    ack_ = 1;
    container_num_ = 0;
}

UnixServer::~UnixServer() {
}

/*
void
register_handler() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = interrupt;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}
*/


void
UnixServer::run() {
    create();
    serve();
}


void
UnixServer::create() {
    struct sockaddr_un server_addr;
    int soval = 1;

    // setup socket address structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, socket_name_, sizeof(server_addr.sun_path) -1);

    // create socket
    server_ = socket(PF_UNIX, SOCK_STREAM, 0);
    if (!server_) {
        perror("socket");
        exit(-1);
    }

    if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1 ) {
        perror("setsockopt");
        exit(-1);
    }

    // call bind to associate the socket with the UNIX file system
    if (bind(server_, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(-1);
    }

    // convert the socket listen for incoming connections
    if (listen(server_, SOMAXCONN) < 0) {
        perror("listen");
        exit(-1);
    }
}

void
UnixServer::serve() {
    int client;
    struct sockaddr_in client_addr;
    socklen_t clientlen = sizeof(client_addr);

    while (1) {
        if ((client = accept(server_, (struct sockaddr *)&client_addr, &clientlen)) > 0)
            handle(client);
    }
    close_socket();
}

void
UnixServer::handle(int client) {
    bool success;
    if (get_ack(client)) {
        success = send_response(client);
        // TODO; bug-increments 4 times
        if (success) container_num_++;
    }
}


bool
UnixServer::get_ack(int client) {
    recv(client, &ack_, sizeof(&ack_), 0);
    printf("return ack_ =%d", ack_);

    if (ack_ == 1)
      return true;
    else
      return false;
}

bool
UnixServer::send_response(int client) {
    int cc;

    if ((cc = send(client, &container_num_, sizeof(int), 0)) < 0) {
        perror("send");
        return false;
    } else {
        return true;
    }
}

void
UnixServer::close_socket() {
    unlink(socket_name_);
}

void
UnixServer::interrupt(int) {
    unlink(socket_name_);
}

