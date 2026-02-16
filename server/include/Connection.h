#ifndef CONNECTION_H
#define CONNECTION_H

#include "Work.h"
#include <stdexcept>
#include <system_error>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <iostream>
#include <memory>      

static constexpr int default_port = 11111;
static constexpr int default_queue_length = 5;

class Connection {
public:
    Connection(int port=default_port, int queue_len=default_queue_length);
    ~Connection();
    void run(Work &worker);
private:
    int sock;
    std::unique_ptr <sockaddr_in> self_addr;
    std::unique_ptr <sockaddr_in> foreign_addr;
    int queue_length;


};




#endif // CONNECTION_H

