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
#include "User.hpp"
#include "Channel.hpp"

using namespace std;
#define BUF_SIZE 1000
#define EVENT_SIZE 100

//int messagecount = 0;

class Server
{
    private:
    //    string name;
    string m_password;
    vector<struct kevent> m_watchList;
    int m_portNum;
    int m_serverSocket;
    struct kevent m_eventList[EVENT_SIZE];
    map<int, User> m_userList;
    map<string, Channel> m_channelList;

    public:
    Server(int portNum, string password);

    ~Server();

    void WatchEvents();

    private:
    void eventHandler(int eventCount);

    void acceptClientSocket();

    void clientEventHandler(struct kevent event);

    void join(string channelName, struct kevent event);
    void quit(std::vector<string> command, struct kevent event);
    void deleteUser(int i);
    void privmsg(std::vector<string> command, struct kevent event);
    void part(std::vector<string> command, struct kevent event);

    string serverMessage(int code, string nickName, string loginName, string channelName, string message);

    string prefixMessage(string nickName, string loginName, string hostName, string command, string message);
    vector<string> split(string str, string delim);
};



#endif