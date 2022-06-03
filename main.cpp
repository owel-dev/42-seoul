#include "Server.hpp"
#include "User.hpp"
#include "Channel.hpp"
#include "commands/command.hpp"
#include "ctime"

#define BUF_SIZE 1000

bool stop = false;

void sigint(int num)
{
	if (num == SIGINT)
	{
        // system("leaks ircserv");
		stop = true;
	}
}

void deleteUserInServer(int fd, User &user, Channel &channel)
{
    vector <string> command;
    command.push_back("QUIT");
    quit(user, channel, command, fd);
    user.deleteUser(fd);
}

bool receiveMessage(int fd, User &user)
{
    char buf[BUF_SIZE];
    int str_len = recv(fd, &buf, BUF_SIZE, 0);                
    if (str_len == 0)
        return false;
    buf[str_len] = 0;
    user.setReadBuffer(fd, buf);
    return true;
}

bool isValidMessage(string message)
{
    int len = message.size();
    if (message[len - 1] != '\n')
        return false;
    return true;
}

vector<string> getSplitedMessage(string message)
{
    vector<string> splitedMessage;
    int len = message.size();
    if (message[len - 1] == '\n' && message[len - 2] != '\r')
        splitedMessage = split(message, "\n");
    else if (message[len - 1] == '\n' && message[len - 2] == '\r')
        splitedMessage = split(message, "\r\n");
    return splitedMessage;
}

void sendWelcomeMessage(int fd, User &user)
{
    time_t now = time(0);
    string date = ctime(&now);
    string nickName = user.getNickName(fd);
    string serverName = user.getHostName(fd);
    user.addUserListString(fd, user.getNickName(fd));
    user.setWriteBuffer(fd, serverMessage(RPL_WELCOME, nickName, "", "", "Welcome to the Internet Relay Network"));
    user.setWriteBuffer(fd, serverMessage(RPL_YOURHOST, nickName, "", "", "Your host is " + serverName + ", running v:1.0"));
    user.setWriteBuffer(fd, serverMessage(RPL_CREATED, nickName, "", "", "This server was created" + date));
    user.setWriteBuffer(fd, serverMessage(RPL_MYINFO, nickName, "", "", serverName + " v:1.0"));
}

int main(int argc, char *argv[])
{
    Server server;
    User user;
    Channel channel;

    signal(SIGINT, sigint);

    try
    {
        if (argc != 3)
            throw "argument error";

        int portNumb = atoi(argv[1]);
        string password = argv[2];

        if (!(1024 <= portNumb && portNumb <= 49151))
            throw "port number error";

        server.createServerSocket(password);
        server.bindServerSocket(AF_INET, INADDR_ANY, portNumb);
        server.listenServerSocket(10);
        server.addServerSocketEvent();
        while (!stop)
        {
            vector<struct kevent> eventList = server.watchEvents(10, NULL);

            for (size_t i = 0; i < eventList.size(); ++i)
            {
                struct kevent currentEvent = eventList[i];
                int currentFd = currentEvent.ident;
                if (currentEvent.flags & EV_ERROR)
                    deleteUserInServer(currentFd, user, channel);
                else if (currentEvent.filter == EVFILT_READ)
                {
                    if (currentFd == server.getServerSocket())
                    {
                        pair<int, string> client = server.acceptClientSocket();
                        user.addUserListInt(client.first);
                        user.setHostName(client.first, client.second);
                    }
                    else
                    {
                        if (!receiveMessage(currentFd, user)) 
                            deleteUserInServer(currentFd, user, channel);
                        string readBuffer = user.getReadBuffer(currentFd);
                        if (!isValidMessage(readBuffer))
                            continue;
                        std::vector<string> message = getSplitedMessage(readBuffer);
                        user.clearReadBuffer(currentFd);
                        vector<string>::iterator it = message.begin();
                        for (; it != message.end(); ++it)
                        {
                            if ((*it).size() == 0)
                                continue;
                            std::vector<string> command = split(*it, " ");
                            if (user.isLogin(currentFd))
                            {
                                if (command[0] == "QUIT")
                                    quit(user, channel, command, currentFd);
                                else if (command[0] == "JOIN")
                                    join(user, channel, command, currentFd);
                                else if (command[0] == "PRIVMSG" || command[0] == "NOTICE")
                                    privmsg(user, channel, command, currentFd);
                                else if (command[0] == "PART")
                                    part(user, channel, command, currentFd);
                                else if (command[0] == "NICK")
                                    nick(user, command, currentFd);
                                else if (command[0] == "KICK")
                                    kick(user, channel, command, currentFd);
                                else if (command[0] == "PASS")
                                    pass(user, server.getPassword(), command, currentFd);
                                else if (command[0] == "PONG")
                                    user.setWriteBuffer(currentFd, "PING :" + user.getHostName(currentFd) + "\r\n");
                                else{
                                    user.setWriteBuffer(currentFd, serverMessage(ERR_UNKNOWNCOMMAND, user.getHostName(currentFd), command[0], "", "Unknown command"));
                                }
                            }
                            else
                            {
                                if (command[0] == "PASS")
                                    pass(user, server.getPassword(), command, currentFd);
                                else if (command[0] == "NICK")
                                    nick(user, command, currentFd);
                                else if (command[0] == "USER")
                                    userCmd(user, command, currentFd);
                                else
                                    user.setWriteBuffer(currentFd, serverMessage(ERR_UNKNOWNCOMMAND, user.getHostName(currentFd), command[0], "", "Unknown command"));
                                if (user.isLogin(currentFd))
                                    sendWelcomeMessage(currentFd, user);
                            }
                        }
                    }
                }
                else if (eventList[i].filter == EVFILT_WRITE)
                {
                    string message = user.getWriteBuffer(currentFd);
                    if (message != "")
                    {
                        send(currentFd, message.c_str(), message.size(), 0);
                        user.clearWriteBuffer(currentFd);
                    }
                    if (user.getStatus(currentFd) == QUIT)
                        user.deleteUser(currentFd);
                }
            }
        }
        server.closeAll(user);
        return 2;
    }
    catch(const char* str)
    {
        std::cerr << str << '\n';
        server.closeAll(user);
        return 1;
    }
    return 0;
}
