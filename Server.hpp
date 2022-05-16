#include <vector>
#include <map>
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

using namespace std;
#define BUF_SIZE 1000

struct User {
  std::string nick; 
  std::string user;
  std::string password;

  User(){
    nick = "";
    user = "";
    password = "";
  }
};

struct User user;

class Server
{
private:
    // string name;
    string m_password;
    // vector<int> m_watchList;
    // map<int, User> m_userList;
    // map<string, Channel> m_channelList;

    vector<struct kevent> m_watchList;

    int m_portNum;
    int m_serverSocket;

public:
    Server(int portNum, string password);
    ~Server();
    void watchSocket();
    void AcceptClientSocket();
    void RecieveAndSend(struct kevent event);
};

Server::Server(int portNum, string password)
{
    m_portNum = portNum;
    m_password = password;
    cout << "m_password: " << m_password <<endl;
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
}

void Server::watchSocket()
{
    int kq;
        
    if ((kq = kqueue()) == -1)
        throw "kqueue error";
    
    struct kevent tempEvent;
    EV_SET(&tempEvent, m_serverSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);

    struct kevent eventList[100];
    while (true) {
        int eventCount = kevent(kq, &m_watchList[0], m_watchList.size(), eventList, 100, NULL);
        if (eventCount == -1)
            throw "kevent error";
        for (int i = 0; i < eventCount; i++) {
            if (eventList[i].flags & EV_ERROR)
                throw "EV error";
            if (eventList[i].filter == EVFILT_READ) {
                if (eventList[i].ident == m_serverSocket)
                    AcceptClientSocket();
                else
                    RecieveAndSend(eventList[i]);
            }
        }
    }
}

void Server::AcceptClientSocket()
{
    struct sockaddr_in clientAddr;
    int clientSocket;

    socklen_t adr_sz = sizeof(clientAddr);
    struct kevent tempEvent;

    clientSocket = accept(m_serverSocket, (struct sockaddr *) &clientAddr, &adr_sz);
    EV_SET(&tempEvent, clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);

    cout << "Connect user. socket number: " << clientSocket << endl;
}

bool isChecked() {
  return (user.nick != "" && user.user != "" && user.password != "");
}

void Server::RecieveAndSend(struct kevent event)
{
    char buf[BUF_SIZE];
    int str_len = read(event.ident, buf, BUF_SIZE);
    buf[str_len] = 0;
    cout << "Recieve: " << endl;
    cout << buf << endl;
    // cout << "hello" << endl;
    std::vector<std::string> command;
    command.push_back(strtok(buf, " ")); // 명령어
    command.push_back(strtok(NULL, "\r\n")); // 인자
    
    if (command[0] == "NICK"){
      user.nick = command[1];
      std::cout << "nick" << std::endl;
    } 
    else if (command[0] == "USER") {
      user.user = command[1];
      std::cout << "user" << std::endl;

    } 
    else if (command[0] == "PASS") {
      std::cout << "pass" << std::endl;
      if (command[1] == m_password) {
      std::cout << "pass: " << command[1] << std::endl;
        user.password = command[1];
      }
    }

    if (!isChecked()) {
      std::cout << "check error" << std::endl;
    cout << "nick: " << user.nick  << ", user: " << user.user << ", password: " << user.password << endl;
      return;
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