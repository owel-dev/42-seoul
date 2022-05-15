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

int serverPassword;

int ListenServerSocket(int portNumber)
{
    int serverSocket;
    struct sockaddr_in serverAddr;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(portNumber);

    if (bind(serverSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) == -1)
        throw "bind error";
    if (listen(serverSocket, 10) == -1)
        throw "listen error";
    return serverSocket;
}

void WatchServerSocket(int servSock, vector<struct kevent> &watchList)
{
    struct kevent tempEvent;

    EV_SET(&tempEvent, servSock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    watchList.push_back(tempEvent);
}

void AcceptClientSocket(int serverSocket, vector<struct kevent> &watchList)
{
    struct sockaddr_in clientAddr;
    int clientSocket;

    socklen_t adr_sz = sizeof(clientAddr);
    struct kevent tempEvent;

    clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddr, &adr_sz);
    EV_SET(&tempEvent, clientSocket, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
    watchList.push_back(tempEvent);
    cout << "Connect user. socket number: " << clientSocket << endl;
}

bool isChecked() {
  if (user.nick != "" && user.user != "" && user.password != "")
    return true;
  return false;
}

void RecieveAndSend(int servSock, struct kevent event, vector<struct kevent> &watchList)
{
    char buf[BUF_SIZE];
    int str_len = read(event.ident, buf, BUF_SIZE);
    buf[str_len] = 0;
    cout << "Recieve: " << endl;
    cout << buf << endl;

    std::vector<std::string> command;
    command.push_back(strtok(buf, " ")); // 명령어
    command.push_back(strtok(NULL, " ")); // 인자
    
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
      if (std::stoi(command[1]) == serverPassword) {
        user.password = command[1];
      }
    }

    if (!isChecked()) {
      std::cout << "check error" << std::endl;
      return;
    }

    for (vector<struct kevent>::iterator it = watchList.begin(); it != watchList.end(); ++it) {
        if (it->ident != servSock) {
            char *str2 = ":ft_irc.com 001 hayelee :Welcome!!!\r\n";
            send(it->ident, str2, strlen(str2), 0);
            // send(it->ident, buf, strlen(buf), 0);
            // cout << "send: " << endl;
            // cout << buf << endl;
        }
    } 
}

int main(int argc, char *argv[])
{
    int serverSocket;

    try {
        if (argc != 3)
            throw "arg error";
        serverSocket = ListenServerSocket(atoi(argv[1]));
        serverPassword = atoi(argv[2]);
        int kq;
        if ((kq = kqueue()) == -1)
            throw "kqueue error";
        vector<struct kevent> watchList;
        WatchServerSocket(serverSocket, watchList);

        struct kevent eventList[100];
        while (true) {
            int eventCount = kevent(kq, &watchList[0], watchList.size(), eventList, 100, NULL);
            if (eventCount == -1)
                throw "kevent error";
            for (int i = 0; i < eventCount; i++) {
                if (eventList[i].flags & EV_ERROR)
                    throw "EV error";
                if (eventList[i].filter == EVFILT_READ) {
                    if (eventList[i].ident == serverSocket)
                        AcceptClientSocket(serverSocket, watchList);
                    else
                        RecieveAndSend(serverSocket, eventList[i], watchList);
                }
            }
        }
    } catch (const char *str) {
        cerr << str << endl;
    }
    close(serverSocket);
    return 0;
}