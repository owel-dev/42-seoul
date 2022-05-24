#include "../Server.hpp"

void Server::nick(std::vector<string> command, struct kevent event)
{
    string newNickName = command[1];
    string nickName = m_userList[event.ident].getNick();
    string loginName = m_userList[event.ident].getUserInfo();
    string hostName = m_userList[event.ident].getHostName();

    std::map<int, User>::iterator it = m_userList.begin();

    //닉네임 중복 검사
    for (; it != m_userList.end(); ++it)
    {
        if (m_userList[it->second.getFd()].getNick() == newNickName)
        {
            m_userList[it->second.getFd()].setWriteBuffer(serverMessage(433, nickName, loginName, "", "Nickname is already in use"));
            return;
        }
    }

    //전체 메세지 전파
    it = m_userList.begin();
    for (; it != m_userList.end(); ++it)
    {
        m_userList[it->second.getFd()].setWriteBuffer(prefixMessage(nickName, loginName, hostName, "NICK", newNickName));
    }

    m_userList[event.ident].setNick(command[1]);
}
