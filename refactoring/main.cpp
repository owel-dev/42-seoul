#include "Server.hpp"
#include "User.hpp"

#define BUF_SIZE 1000


vector<string> split(string str, string delim) // ""
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



int main(int argc, char *argv[])
{
    Server server;
    User user;

    int portNumb = atoi(argv[1]);
    string password = argv[2];

    server.createServerSocket(password);
    server.bindServerSocket(AF_INET, INADDR_ANY, portNumb);
    server.listenServerSocket(10);

    server.addServerSocketEvent();
    while (42)
    {
        vector<struct kevent> eventList = server.watchEvents(100, NULL);
        for (int i = 0; i < eventList.size(); ++i)
        {
            struct kevent currentEvent = eventList[i];
            int currentFd = currentEvent.ident;
            if (currentEvent.flags & EV_ERROR)
            {
                // deleteUser(i);
                return 0;
            }
            else if (currentEvent.filter == EVFILT_READ)
            {
                if (currentFd == server.getServerSocket())
                {
                    pair<int, string> client = server.acceptClientSocket();

                    user.addUser(client.first);
                    user.setHostName(client.first, client.second);
                    std::cout << "main currentFd 62 : " << client.first << std::endl;
                }
                else
                {
                    // clientEventHandler(currentEvent);
                    char buf[BUF_SIZE];
                    // memset(buf, 0, sizeof(buf));
                    int str_len = read(currentFd, buf, BUF_SIZE);
                    if (str_len == 0)
                    {
                        close(currentFd);
                        return 0;
                    }
                    buf[str_len] = 0;
                    cout << "Recieve: " << endl;
                    cout << buf << endl;
                    std::vector<string> message = split(buf, "\r\n");

                    vector<string>::iterator it = message.begin();
                    for (; it != message.end(); ++it)
                    {
                        std::vector<string> command = split(*it, " ");

                        if (user.isLogin(currentFd))
                        {
                            // if (command[0] == "QUIT")
                            // {
                            //     quit(command, currentFd);
                            // }
                            // else if (command[0] == "JOIN")
                            // {
                            //     join(command[1], currentFd);
                            // }
                            // else if (command[0] == "PRIVMSG")
                            // {
                            //     privmsg(command, currentFd);
                            // }
                            // else if (command[0] == "PART")
                            // {
                            //     part(command, currentFd);
                            // }
                            // else if (command[0] == "NICK")
                            // {
                            //     nick(command, currentFd);
                            // }
                            // else if (command[0] == "USER")
                            // {
                            //     // user(command, currentFd);
                            // }
                            // else if (command[0] == "KICK")
                            // {
                            //     kick(command, currentFd);
                            // }
                            // else
                            // {
                            //     cout << "|" << command[0] << "|" << endl;
                            // }
                        }
                        else
                        {
                            if (command[0] == "PASS" && command[1] == server.getPassword())
                            {
                                std::cout << "In pass" << std::endl;
                                user.setPassword(currentFd, command[1]);
                            }
                            else if (command[0] == "NICK")
                            {
                                std::cout << "In nick" << std::endl;
                                user.setNickName(currentFd, command[1]);
                            }
                            else if (command[0] == "USER")
                            {
                                std::cout << "In user" << std::endl;
                                user.setLoginName(currentFd, command[1]);
                                std::cout << "nickname: " << user.getNickName(currentFd) << std::endl;
                                std::cout << "hostname: " << currentFd << " | " << user.getHostName(currentFd) << std::endl;
                                std::cout << "loginname: " << user.getLoginName(currentFd) << std::endl;
                                std::cout << "password: " << user.getPassword(currentFd) << std::endl;
                            }
                            if (user.isLogin(currentFd))
                            {
                                string message = ":ft_irc.com 001 " + user.getNickName(currentFd) + " :Welcome!!\r\n";
                                user.setWriteBuffer(currentFd, message);
                                string message1 = user.getWriteBuffer(currentFd);
                                std::cout << "message1: |" << message << "|" << std::endl;                
                            }
                        }
                    }
                }
            }
            else if (eventList[i].filter == EVFILT_WRITE)
            {
                // std::cout << "main.cpp line 141" << std::endl;
                string message = user.getWriteBuffer(currentFd);
                // std::cout << "message: |" << message << "|" << std::endl;                
                if (message != "") 
                {
                    send(currentFd, message.c_str(), message.size(), 0);
                    std::cout << "send to " << user.getNickName(currentFd) << ": " << message << std::endl;
                    user.clearWriteBuffer(currentFd);
                }
                // map<int, User>::iterator it = m_userList.begin();
                // for (;it != m_userList.end(); ++it) {
                //     User &user = it->second;
                //     if (user.getWriteBuffer() == "")
                //         continue;
                //     send(user.m_fd, user.getWriteBuffer().c_str(), user.getWriteBuffer().size(), 0);
                //     cout << "send to " << user.getNick() << ": " << user.getWriteBuffer() << endl;
                //     user.clearWriteBuffer();
                //     if (user.getStatus() == QUIT) {
                //         deleteUser(i);
                // return 0;
                //     }
            }
        }
    }
    return 0;
}
