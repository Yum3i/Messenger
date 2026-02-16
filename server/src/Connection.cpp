#include "../include/Connection.h"
#include <stdexcept>
#include <system_error>
#include <netinet/in.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <thread>

Connection::Connection(int port, int queue_len) :
    sock(socket(AF_INET, SOCK_STREAM, 0)),
    self_addr(new sockaddr_in),
    foreign_addr(new sockaddr_in),
    queue_length(queue_len)
{
    int reuse = 1;
    if (sock == -1){
        throw std::system_error(errno, std::generic_category(), "Socket creation failed");
    }
    int rc = setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    if (rc == -1){
        throw std::system_error(errno, std::generic_category(), "Set socket options failed");
    }
    self_addr->sin_family = AF_INET;
    self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
    self_addr->sin_port = htons(port);
    if (bind(sock, reinterpret_cast<const sockaddr*>(self_addr.get()), sizeof(sockaddr_in)) == -1){
        throw std::system_error(errno, std::generic_category(), "Bind failed");
    }

}

Connection::~Connection(){
    close(sock);
}

void Connection::run(Work &worker){
    if (listen(sock, queue_length)== -1){
        throw std::system_error(errno, std::generic_category(), "Listen failed");
    }
    socklen_t socklen = sizeof(sockaddr_in);
    while (true)
    {
        int work_sock = accept(sock, reinterpret_cast<sockaddr*>(foreign_addr.get()), &socklen);
        if (work_sock == -1)
            throw std::system_error(errno, std::generic_category(), "Bind failed");
        std::thread client_thread([this, &worker, work_sock](){
            std::string client_ip = inet_ntoa(foreign_addr->sin_addr);
            std::cout << "Client connected: " << client_ip << std::endl;
            
            while (true)
            {
                std::string msg = worker.reception(work_sock);
                if (msg == "disconnected") {
                    break;  // Выйти из внутреннего цикла, чтобы обработать следующего клиента
                }
                worker.send_message(work_sock, msg);
            }
            std::cout << "Client disconnected "<< client_ip << std::endl;
            close(work_sock);
        });
        client_thread.detach();
    }
    
}

