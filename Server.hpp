#include <vector>
#include <map>
#include <unistd.h>
#include <utility>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <vector>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include "User.hpp"

using namespace std;
#define BUF_SIZE 1000
#define EVENT_SIZE 100

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

  public:
  Server(int portNum, string password);

  ~Server();

  void WatchEvents();

  private:
  void eventHandler(int eventCount);

  void acceptClientSocket();

  void clientEventHandler(struct kevent event);

};

Server::Server(int portNum, string password) : m_portNum(portNum), m_password(password)
{
    if ((m_serverSocket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        throw "socket() error";

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(m_portNum);

    if (bind(m_serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1)
        throw "bind() error";
    if (listen(m_serverSocket, 10) == -1)
        throw "listen() error";
}

Server::~Server()
{
    close(m_serverSocket);
}

void Server::WatchEvents()
{
    int kq;

    if ((kq = kqueue()) == -1)
        throw "kqueue error";

    struct kevent tempEvent;
    EV_SET(&tempEvent, m_serverSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);

    while (true) {
        int eventCount = kevent(kq, &m_watchList[0], m_watchList.size(), m_eventList, EVENT_SIZE, NULL);
        if (eventCount == -1)
            throw "kevent error";
        eventHandler(eventCount);
    }
}

void Server::eventHandler(int eventCount)
{
    for (int i = 0; i < eventCount; i++) {
        if (m_eventList[i].flags & EV_ERROR)
            throw "EV error";
        if (m_eventList[i].filter == EVFILT_READ) {
            if (m_eventList[i].ident == m_serverSocket)
                acceptClientSocket();
            else
                clientEventHandler(m_eventList[i]);
        }
    }
}

void Server::acceptClientSocket()
{
    struct sockaddr_in clientAddr;
    int clientSocket;

    socklen_t adr_sz = sizeof(clientAddr);
    struct kevent tempEvent;

    clientSocket = accept(m_serverSocket, (struct sockaddr *) &clientAddr, &adr_sz);
    EV_SET(&tempEvent, clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);
    cout << "previous insert" << endl;
    m_userList.insert(make_pair(clientSocket, User(clientSocket)));
    cout << "after insert" << endl;
    cout << "Connect user. socket number: " << clientSocket << endl;
}


//bool isChecked(User &user)
//{
//    return (user.m_nick != "" && user.userInfo != "" && user.password != "");
//}

void Server::clientEventHandler(struct kevent event)
{
    char buf[BUF_SIZE];
    int str_len = read(event.ident, buf, BUF_SIZE);
    buf[str_len] = 0;
    cout << "Recieve: " << endl;
    cout << buf << endl;
    std::vector<std::string> command;
    char *temp;
    command.push_back(strtok(buf, " \r\n"));
    if ((temp = strtok(NULL, " \r\n")))
        command.push_back(temp);
    if ((temp = strtok(NULL, "\r\n")))
        command.push_back(temp);

//    User &user = m_userList[event.ident];
    if (m_userList[event.ident].isChecked()) {
        if (command[0] == "JOIN") {
            m_userList[event.ident].set_channelName(command[1]);
            std::cout << "nick" << std::endl;
        }
    } else {
        if (command[0] == "NICK") {
            m_userList[event.ident].set_nick(command[1]);
            std::cout << "nick" << std::endl;
        } else if (command[0] == "USER") {
            m_userList[event.ident].set_userInfo(command[1]);
            std::cout << "user" << std::endl;
        } else if (command[0] == "PASS") {
            std::cout << "pass" << std::endl;
            if (command[1] == m_password) {
                std::cout << "======pass: " << command[1] << std::endl;
                m_userList[event.ident].set_password(command[1]);
            }
        }
    }

    for (vector<struct kevent>::iterator it = m_watchList.begin(); it != m_watchList.end(); ++it) {
        if (it->ident != m_serverSocket) {
            char *str2 = ":ft_irc.com 001 hayelee :Welcome!!\r\n";
            send(it->ident, str2, strlen(str2), 0);
            // send(it->ident, buf, strlen(buf), 0);
            // cout << "send: " << endl;
            // cout << buf << endl;
        }
    }
}