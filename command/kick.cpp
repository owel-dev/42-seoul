#include "../Server.hpp"

void Server::kick(std::vector<string> command, struct kevent event)
{
    string channelName = command[1];
    string target = command[2];
    map<int, User>::iterator it = m_channelList[channelName].m_userList.begin();
    User &sender = m_userList[event.ident];
//    string msg = channelName + " " + target;
    if (event.ident == m_channelList[channelName].m_admin)
    {
        for (;it != m_channelList[channelName].m_userList.end(); ++it)
        {
            User &receiver = it->second;
            m_userList[receiver.getFd()].setWriteBuffer(prefixMessage(sender.getNick(), sender.getUserInfo(), sender.getHostName(), "kick", channelName, target, command[3]));

//            if (receiver.getNick() == target)
//            {
//                m_channelList[channelName].m_userList.erase(receiver.getFd());
//            }
        }
    }
    else
    {
        m_userList[event.ident].setWriteBuffer(
                serverMessage(481, m_userList[event.ident].getNick(), "Permission Denied- You're not an IRC operator"));
    }
}
