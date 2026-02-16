#include "../include/Connection.h"
#include <stdexcept>
#include <system_error>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <iostream>
#include <memory>
#include <unistd.h>
#include<string.h>


Connection::Connection(int port) :
    sock(socket(AF_INET, SOCK_STREAM, 0)),
    self_addr(new sockaddr_in),
    serv_addr(new sockaddr_in)
{
    self_addr->sin_family = AF_INET;
    self_addr->sin_addr.s_addr = 0;
    self_addr->sin_port = 0;
    
    serv_addr->sin_family = AF_INET;
    serv_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr->sin_port = htons(port);
}
int Connection::run() {
    if (sock == -1)
        throw std::system_error(errno, std::generic_category(), "Socket creation failed");
    int rc = bind(sock, reinterpret_cast<sockaddr*>(self_addr.get()), sizeof(sockaddr_in));
    if (rc == -1) 
        throw std::system_error(errno, std::generic_category(), "Bind failed");
    rc = connect(sock, reinterpret_cast<sockaddr*>(serv_addr.get()), sizeof(sockaddr_in));
    if (rc == -1) 
            throw std::system_error(errno, std::generic_category(), "Connect failed");
    return rc;
}
void Connection::send_message(){
        std::string msg;
        std::getline(std::cin, msg);
        msg += "\n";
        ssize_t bytes_sent = send(sock, msg.c_str(), msg.size(), 0);
        if (bytes_sent == -1)
            throw std::system_error(errno, std::generic_category(), "Send failed");
}


void Connection::reception() {    
        

        int buffer = 1024;
        std::unique_ptr<char[]> buf(new char[buffer]);
        int rc = 0;
        while (true){
            rc = recv(sock, buf.get(), buffer, MSG_PEEK);
            if (rc == 0) {
            std::cout << "Client disconnected " << std::endl;
            return;  // Выйти из reception()
         }
            if (rc < buffer) {
                break;
            }
            buffer *= 2;
            buf = std::unique_ptr<char[]>(new char[buffer]);
            
        }
        std::string msg(buf.get(), rc);
        rc = recv(sock, nullptr, rc, MSG_TRUNC);
        std::cout << "Received message: " << msg << std::endl;
        msg = "";

        
    
}
