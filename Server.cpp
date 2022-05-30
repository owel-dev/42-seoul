#include "Server.hpp"

void Server::createServerSocket(string password)
{
    if ((m_socket = socket(PF_INET, SOCK_STREAM, 0)) == -1)
        throw "socket() error";
    m_password = password;
}

void Server::bindServerSocket(int family, u_int32_t addr, int portNumb)
{
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = family;
    serverAddr.sin_addr.s_addr = htonl(addr);
    serverAddr.sin_port = htons(portNumb);

    if (bind(m_socket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1)
        throw "bind() error";
}

void Server::listenServerSocket(int backlog)
{
    if (listen(m_socket, backlog) == -1)
        throw "listen() error";
}

void Server::addServerSocketEvent()
{
    if ((m_kq = kqueue()) == -1)
        throw "kqueue error";        

    struct kevent tempEvent;
    EV_SET(&tempEvent, m_socket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);
}

vector<struct kevent> Server::watchEvents(int eventSize, const timespec *timeout)
{

    struct kevent eventList[eventSize];

    int eventCount = kevent(m_kq, &m_watchList[0], m_watchList.size(), eventList, eventSize, timeout);
    if (eventCount == -1)
        throw "kevent error";
    m_watchList.clear();
    vector<struct kevent> v_eventList(eventList, eventList + eventCount);
    return (v_eventList);
}

int Server::getServerSocket()
{
    return m_socket;
}

pair<int, string> Server::acceptClientSocket()
{
    struct sockaddr_in clientAddr;
    int clientSocket;
    
    socklen_t adr_sz = sizeof(clientAddr);
    struct kevent tempEvent;

    clientSocket = accept(m_socket, (struct sockaddr *) &clientAddr, &adr_sz);
    EV_SET(&tempEvent, clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);
	EV_SET(&tempEvent, clientSocket, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
    m_watchList.push_back(tempEvent);
    string hostName = inet_ntoa(clientAddr.sin_addr);
    // cout << "-----Connect user. socket number: " << clientSocket << "------" << endl;
     
    return (make_pair(clientSocket, hostName));
}

string Server::getPassword(){
    return m_password;
}

void Server::closeAll(User &user)
{
    close(m_socket); 
    map<string, int> userList = user.getUserListString();
    map<string, int>::iterator it = userList.begin();

    for(; it != userList.end(); ++it){
        close(it->second);
    }
}