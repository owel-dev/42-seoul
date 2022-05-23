#include "../Server.hpp"

void Server::part(std::vector<string> command, struct kevent event)
{
    
    // 해당 채널의 유저 목록을 돌면서 메시지 전송
    string channelName = command[1];
    string message = command[2];
    map<int, User>::iterator it = m_channelList[channelName].m_userList.begin();
    User &sender = m_userList[event.ident];
    string msg = channelName + " " + message;
    for (;it != m_channelList[channelName].m_userList.end(); ++it)
    {
        User &receiver = it->second;
        m_userList[receiver.getFd()].setWriteBuffer(prefixMessage(sender.getNick(), sender.getUserInfo(), sender.getHostName(), "part", msg));
    }
    m_channelList[channelName].m_userList.erase(event.ident);
}