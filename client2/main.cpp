#include <iostream>
#include "Connection.h"
#include <string>

int main()
{
    try
    {
        Connection conn;
        conn.run();
        while (true)
        {
            conn.send_message();
            conn.reception();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}
