#include<iostream>
#include"../include/Connection.h"
#include <thread>


int main()
{
    try
    {
        Work worker;
        Connection server_connection;
        server_connection.run(worker);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}