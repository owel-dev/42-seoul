#include "Server.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    try {
        
        if (argc != 3)
            throw "arg error";
        
        Server server(atoi(argv[1]), argv[2]);
        server.WatchEvents();

    } catch (const char *str) {
        cerr << str << endl;
    }
    return 0;
}