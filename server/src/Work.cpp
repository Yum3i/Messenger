#include"../include/Work.h"
#include <unistd.h>
#include <memory>
#include <sys/socket.h>
#include <string>
#include <iostream> 

Work::Work() : work_sock(-1) {}

void Work::send_message(int work_sock, std::string msg){
        msg += "\n";
        ssize_t bytes_sent = send(work_sock, msg.c_str(), msg.size(), 0);
        if (bytes_sent == -1)
            throw std::system_error(errno, std::generic_category(), "Send failed");
}

std::string Work::reception(int work_sock) {
        int buffer = 1024;
        std::unique_ptr<char[]> buf(new char[buffer]);
        int rc = 0;
        while (true){
            rc = recv(work_sock, buf.get(), buffer, MSG_PEEK);
            if (rc <= 0) {
                std::cout << "Client disconnected " << std::endl;
                return "disconnected";  // Выйти из reception()
            }
            if (rc < buffer) {
                break;
            }
            buffer *= 2;
            buf = std::unique_ptr<char[]>(new char[buffer]);
            
        }
        std::string msg(buf.get(), rc);
        rc = recv(work_sock, nullptr, rc, MSG_TRUNC);
        std::cout << "Received message: " << msg << std::endl;
        if (rc == -1) 
            throw std::system_error(errno, std::generic_category(), "Connect failed");
        return msg;
        
}
Work::~Work() {
    if (work_sock != -1) {
        close(work_sock);
    }
}
