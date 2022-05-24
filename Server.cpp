#include "Server.hpp"

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
    for (int i = 0; i < eventCount; i++) 
    {
        if (m_eventList[i].flags & EV_ERROR)
        {
            deleteUser(i);
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
                cout << "send to " << user.getNick() << ": " << user.getWriteBuffer() << endl;
                user.clearWriteBuffer();
                if (user.getStatus() == QUIT) {
                    deleteUser(i);
                    return;
                }
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
                quit(command, event);
            }
            else if (command[0] == "JOIN") {
                join(command[1], event);
            } else if (command[0] == "PRIVMSG") {
                privmsg(command, event);
            } else if (command[0] == "PART") {
                part(command, event);
            } else if (command[0] == "NICK") {
                kick(command, event);
            } else if (command[0] == "USER") {
                // user(command, event);
            } else if (command[0] == "KICK") {
                 kick(command, event);
            }
            else {
                cout << "|" << command[0] << "|" << endl;
            }
        } else {
            if (command[0] == "PASS" && command[1] == m_password) {
                m_userList[event.ident].setPassword(command[1]);
            }
            else if (command[0] == "NICK") {
                m_userList[event.ident].setNick(command[1]);
            } 
            else if (command[0] == "USER") {
                m_userList[event.ident].setLoginName(command[1]);
            }
            if (m_userList[event.ident].isChecked()) {
                User &user = m_userList[event.ident];
                user.setWriteBuffer(":ft_irc.com 001 " + user.getNick() + " :Welcome!!\r\n");
            }
        }
    }
}

string Server::serverMessage(int code, string nickName, string message)
{
    string result = "";
    result += ":ft_irc.com ";
    result += to_string(code);
    result += " ";
    result += nickName;
    result += " ";
    result += message;
    result += "\r\n";
    return result;
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

string Server::prefixMessage(string nickName, string loginName, string hostName, string command, string channel, string target, string message)
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
    result += channel;
    result += " ";
    result += target;
    result += " ";
    result += message;
    result += "\r\n";
    return result;
}

vector<string> Server::split(string str, string delim) // ""
{
    vector<string> ret;
    int delim_len = delim.size();
    size_t cut;
    while ((cut = str.find(delim)) != string::npos)
    {
        if (str[0] == ':') {
            break;
        }
        string word = str.substr(0, cut);
        ret.push_back(word);
        str = str.substr(cut + delim_len);
    }
    if (str != "")
        ret.push_back(str);
    return ret;
}
