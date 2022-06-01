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
                if (currentEvent.flags & EV_ERROR){
                    user.deleteUser(currentFd);
                }
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
                        char buf[BUF_SIZE];
                        int str_len = recv(currentFd, &buf, BUF_SIZE, 0);                
                        if (str_len == 0)
                            continue;
                        buf[str_len] = 0;
                        cout << "Recieve: " << buf << endl;
                        std::vector<string> message = split(buf, "\r\n");
                        vector<string>::iterator it = message.begin();
                        for (; it != message.end(); ++it)
                        {
                            std::vector<string> command = split(*it, " ");
                            std::cout << "command[0]: |" << command[0] << "|, command[1]: |" << command[1] << "|" << std::endl;
                            if (user.isLogin(currentFd))
                            {
                                if (command[0] == "QUIT")
                                    quit(user, channel, command[1], currentFd);
                                else if (command[0] == "JOIN")
                                    join(user, channel, command[1], currentFd);
                                else if (command[0] == "PRIVMSG" || command[0] == "NOTICE")
                                    privmsg(user, channel, command, currentFd);
                                else if (command[0] == "PART")
                                    part(user, channel, command, currentFd);
                                else if (command[0] == "NICK")
                                    nick(user, command[1], currentFd);
                                else if (command[0] == "KICK")
                                    kick(user, channel, command, currentFd);
                                else if (command[0] == "PONG")
                                    user.setWriteBuffer(currentFd, "PING :" + user.getHostName(currentFd) + "\r\n");
                            }
                            else
                            {
                                if (command[0] == "PASS") {
                                    pass(user, server.getPassword(), command, currentFd);
                                }
                                else if (command[0] == "NICK") {
                                    nick(user, command[1], currentFd);
                                }
                                else if (command[0] == "USER") {
                                    userCmd(user, command, currentFd);
                                }
                                if (user.isLogin(currentFd))
                                {
                                    time_t now = time(0);
                                    string date = ctime(&now);
                                    string nickName = user.getNickName(currentFd);
                                    string serverName = user.getHostName(currentFd);
                                    user.addUserListString(currentFd, user.getNickName(currentFd));
                                    user.setWriteBuffer(currentFd, serverMessage(RPL_WELCOME, nickName, "", "", "Welcome to the Internet Relay Network"));
                                    user.setWriteBuffer(currentFd, serverMessage(RPL_YOURHOST, nickName, "", "", "Your host is " + serverName + ", running v:1.0"));
                                    user.setWriteBuffer(currentFd, serverMessage(RPL_CREATED, nickName, "", "", "This server was created" + date));
                                    user.setWriteBuffer(currentFd, serverMessage(RPL_MYINFO, nickName, "", "", serverName + " v:1.0"));
                                }
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
                        std::cout << "send to " << user.getNickName(currentFd) << ": " << message << std::endl;
                        user.clearWriteBuffer(currentFd);
                    }

                    if (user.getStatus(currentFd) == QUIT)
                        user.deleteUser(currentFd);
                }
            }
        }
        server.closeAll(user);
        return 1;
    }
    catch(const char* str)
    {
        std::cerr << str << '\n';
        server.closeAll(user);
        return 1;
    }
    return 0;
}
