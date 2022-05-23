#include "../Server.hpp"

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
        string newUserNickName = m_userList[newFd].getNick();
        string newUserLoginName = m_userList[newFd].getUserInfo();
        string newUserHostName = m_userList[newFd].getHostName();
        m_userList[it->second.getFd()].setWriteBuffer(prefixMessage(newUserNickName, newUserLoginName, newUserHostName, "JOIN", channelName));
        if (it->second.m_fd == newFd) { // 방금 join한 유저에게 메시지 전송
            m_userList[newFd].setWriteBuffer(serverMessage(332, newUserNickName, newUserLoginName, channelName, "A timey-wimey channel"));
            m_userList[newFd].setWriteBuffer(serverMessage(353, newUserNickName, newUserLoginName, channelName, channel.getUserList(newFd)));
            m_userList[newFd].setWriteBuffer(serverMessage(366, newUserNickName, newUserLoginName, channelName, "End of NAMES list"));
        }
    }
}