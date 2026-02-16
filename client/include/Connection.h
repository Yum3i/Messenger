#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdexcept>
#include <system_error>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <iostream>
#include <memory>

static constexpr int default_port = 11111;

class Connection {
public:
    Connection(int port=default_port);
    int run();
    void reception();
    void send_message();

private:
    int sock;
    std::unique_ptr<sockaddr_in> self_addr;
    std::unique_ptr<sockaddr_in> serv_addr;  
};
#endif