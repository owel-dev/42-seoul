#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <vector>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include "Server.hpp"
#include <signal.h>

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