#ifndef SERVER_HPP
#define SERVER_HPP

#include <map>
#include <unistd.h>
#include <utility>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <vector>
#include <string>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <queue>

#define EVENT_SIZE 100
using namespace std;

class Server {
    private:
        int m_kq;
        int m_socket;
        vector<struct kevent> m_watchList;
        string m_password;

    public:
        void createServerSocket(string password);
        void bindServerSocket(int family, u_int32_t addr, int portNumb);
        void listenServerSocket(int backlog);
        void addServerSocketEvent();
        vector<struct kevent> watchEvents(int eventSize, const timespec *timeout);

        int getServerSocket();
        string getPassword();
        pair<int, string> acceptClientSocket();
};       

#endif