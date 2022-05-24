#include "../Server.hpp"

void Server::privmsg(std::vector<string> command, struct kevent event)
{
    cout << "message: |" << command[2] << "|" << endl;
    if (command[1].substr(0, 1) == "#") // 채널 메시지
    {
        // 해당 채널의 유저 목록을 돌면서 메시지 전송
        map<int, User&>::iterator it = m_channelList[command[1]].m_userList.begin();
        User &sender = m_userList[event.ident];
        string message = "" + command[1] + " " + command[2];
        for (;it != m_channelList[command[1]].m_userList.end(); ++it)
        {
            User &receiver = it->second;
            if (receiver.getFd() != sender.getFd())
                m_userList[receiver.getFd()].setWriteBuffer(prefixMessage(sender.getNick(), sender.getUserInfo(), sender.getHostName(), "privmsg", message));
        }
    }
    else 
    {
        map<int, User>::iterator it = m_userList.begin();
        for (;it != m_userList.end(); ++it) 
        {
            if (it->second.getNick() == command[1]) {
                break;
            }
        }
        if (it == m_userList.end()) {
            return;
        }
        User &sender = m_userList[event.ident];
        User &receiver = it->second;
        string message = "" + receiver.getNick() + " " + command[2];

        m_userList[receiver.getFd()].setWriteBuffer(prefixMessage(sender.getNick(), sender.getUserInfo(), sender.getHostName(), "privmsg", message));
    }
}