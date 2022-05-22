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

int messagecount = 0;

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
  int first_fd = 0;

  public:
  Server(int portNum, string password);

  ~Server();

  void WatchEvents();

  private:
  void eventHandler(int eventCount);

  void acceptClientSocket();

  void clientEventHandler(struct kevent event);

  void join(string channelName, struct kevent event);

    string serverMessage(int code, string nickName, string loginName, string channelName, string message);

  string prefixMessage(string nickName, string loginName, string hostName, string command, string message);
  vector<string> split(string str, string delim);


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
    // fcntl(m_serverSocket, F_SETFL, O_NONBLOCK);
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
        {
            vector<struct kevent>::iterator it = m_watchList.begin();
            for (;it != m_watchList.end(); ++it)
            {
                if (it->ident == m_eventList[i].ident) {
                    m_watchList.erase(it);
                    break;
                }
            }
            m_userList.erase(m_eventList[i].ident);
            close(m_eventList[i].ident);
            return;
        }
        else if (m_eventList[i].filter == EVFILT_READ) {
            if (m_eventList[i].ident == m_serverSocket)
                acceptClientSocket();
            else
                clientEventHandler(m_eventList[i]);
        } else if (m_eventList[i].filter == EVFILT_WRITE) {
            map<int, User>::iterator it = m_userList.begin();
            for (;it != m_userList.end(); ++it) {
                User &user = it->second;
                if (user.getWriteBuffer() == "")
                    continue;
                send(user.m_fd, user.getWriteBuffer().c_str(), user.getWriteBuffer().size(), 0);
                cout << "######send to " << user.get_nick() << ":\n" << user.getWriteBuffer() << std::endl;
                user.clearWriteBuffer();
            }
        }
    }
}

void Server::acceptClientSocket()
{
    struct sockaddr_in clientAddr;
    int clientSocket;

    socklen_t adr_sz = sizeof(clientAddr);
    struct kevent tempEvent;

    // fcntl(clientSocket, F_SETFL, O_NONBLOCK);
    clientSocket = accept(m_serverSocket, (struct sockaddr *) &clientAddr, &adr_sz);
    EV_SET(&tempEvent, clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);
	EV_SET(&tempEvent, clientSocket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);
    m_userList.insert(make_pair(clientSocket, User(clientSocket)));
    m_userList[clientSocket].setHostName(inet_ntoa(clientAddr.sin_addr));
    cout << "-----Connect user. socket number: " << clientSocket << "------" << endl;
}

void Server::clientEventHandler(struct kevent event)
{
    char buf[BUF_SIZE];
    // memset(buf, 0, sizeof(buf));
    int str_len = read(event.ident, buf, BUF_SIZE);
    if (str_len == 0) {
        close(event.ident); 
        return;
    }
    buf[str_len] = 0;
    cout << "Recieve: " << endl;
    cout << buf << endl;
    std::vector<string> message = split(buf, "\r\n");

    vector<string>::iterator it = message.begin();
    for (;it != message.end(); ++it) {
        std::vector<string> command = split(*it, " ");

        if (m_userList[event.ident].isChecked()) {
            if (command[0] == "QUIT") { 
                close(event.ident);
                cout << "Quit Check" << endl;
            }
            else if (command[0] == "JOIN") {
                join(command[1], event);
            } else if (command[0] == "PRIVMSG") {
                if (command[1].substr(0, 1) == "#") // 채널 메시지
                {
                    cout << "------------CHANNEL MESSAGE-------------" << endl;
                    // 해당 채널의 유저 목록을 돌면서 메시지 전송
                    map<int, User>::iterator it = m_channelList[command[1]].m_userList.begin();
                    User &sender = m_userList[event.ident];
                    string message = "" + command[1] + " " + command[2];
                    for (;it != m_channelList[command[1]].m_userList.end(); ++it)
                    {
                        User &receiver = it->second;
                        if (receiver.getFd() != sender.getFd())
                            m_userList[receiver.getFd()].setWriteBuffer(prefixMessage(sender.get_nick(), sender.get_userInfo(), sender.getHostName(), "privmsg", message));
                    }
                }
                else 
                {
                    cout << "------------DIRECT MESSAGE-------------" << endl;
                    map<int, User>::iterator it = m_userList.begin();
                    for (;it != m_userList.end(); ++it) 
                    {
                        if (it->second.get_nick() == command[1]) {
                            break;
                        }
                    }
                    User &sender = m_userList[event.ident];
                    User &receiver = it->second;
                    string message = "" + receiver.get_nick() + " " + command[2];

                    m_userList[receiver.getFd()].setWriteBuffer(prefixMessage(sender.get_nick(), sender.get_userInfo(), sender.getHostName(), "privmsg", message));
                }
            } 
            else {
                cout << "|" << command[0] << "|" << endl;
            }
        } else {
            if (command[0] == "PASS" && command[1] == m_password) {
                m_userList[event.ident].set_password(command[1]);
                cout << "line 224" << endl;
            }
            else if (command[0] == "NICK") {
                m_userList[event.ident].set_nick(command[1]);
                cout << "line 228" << endl;
            } 
            else if (command[0] == "USER") {
                m_userList[event.ident].set_loginName(command[1]);
                cout << "line 232" << endl;
            }
            if (m_userList[event.ident].isChecked()) {
                User &user = m_userList[event.ident];
                user.setWriteBuffer(":ft_irc.com 001 " + user.get_nick() + " :Welcome!!\r\n");
            }
        }
    }
}

void Server::join(string channelName, struct kevent event)
{
    int newFd = event.ident;
    if (!m_channelList.count(channelName)) { // 채널리스트에 채널 추가
        m_channelList.insert(make_pair(channelName, Channel()));
        m_channelList[channelName].setName(channelName);
        m_channelList[channelName].setAdmin(event.ident);    
    }      
    m_channelList[channelName].addUser(m_userList[event.ident]); // 채널에 유저 추가
    // 채널의 유저리스트를 돌면서 방금 join한 유저를 제외한 다른 유저들에게 메시지 전송
    Channel &channel = m_channelList[channelName];
    map<int, User> channelUserList = channel.m_userList;
    map<int, User>::iterator it = channelUserList.begin();
    for (;it != channelUserList.end(); ++it) {
        string newUserNickName = m_userList[newFd].get_nick();
        string newUserLoginName = m_userList[newFd].get_userInfo();
        string newUserHostName = m_userList[newFd].getHostName();
        m_userList[it->second.getFd()].setWriteBuffer(prefixMessage(newUserNickName, newUserLoginName, newUserHostName, "JOIN", channelName));
        if (it->second.m_fd == newFd) { // 방금 join한 유저에게 메시지 전송
            m_userList[newFd].setWriteBuffer(serverMessage(332, newUserNickName, newUserLoginName, channelName, "A timey-wimey channel"));
            m_userList[newFd].setWriteBuffer(serverMessage(353, newUserNickName, newUserLoginName, channelName, channel.getUserList(newFd)));
            m_userList[newFd].setWriteBuffer(serverMessage(366, newUserNickName, newUserLoginName, channelName, "End of NAMES list"));
        }
    }
}

string Server::serverMessage(int code, string nickName, string loginName, string channelName, string message)
{
    string result = "";
    result += ":ft_irc.com ";
    result += to_string(code);
    result += " ";
    result += nickName;
    result += " ";
    result += loginName;
    if (code == 332 || code == 366) {
        result += " ";
    } else {
        result += "= ";
    }
    result += channelName;
    result += " :";
    result += message;
    result += "\r\n";
    return result;
}

string Server::prefixMessage(string nickName, string loginName, string hostName, string command, string message)
{
    string result = ":";
    result += nickName;
    result += "!";
    result += loginName;
    result += "@";
    result += hostName;
    result += " ";
    result += command;
    result += " ";
    result += message;
    result += "\r\n";
    return result;
}
//10.19.248.56


// vector<string> Server::split(string str, char Delimiter) {
//     istringstream iss(str);             // istringstream에 str을 담는다.
//     string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
 
//     vector<string> result;
 
//     // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
//     while (getline(iss, buffer, Delimiter)) {
//         result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
//     }
 
//     return result;
// }

vector<string> Server::split(string str, string delim)
{
    vector<string> ret;
    int delim_len = delim.size();
    size_t cut;
    while ((cut = str.find(delim)) != string::npos)
    {
        string word = str.substr(0, cut);
        ret.push_back(word);
        str = str.substr(cut + delim_len);
        // std::cout << "hello" << std::endl;
    }
    // std::cout << str << std::endl;
    if (str != "")
        ret.push_back(str);
    return ret;
}





#endif