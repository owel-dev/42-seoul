#include "Channel.hpp"

Channel::Channel(){};

void Channel::addUser(User &user)
{
    m_userList.insert(pair<int, User&>(user.m_fd, user));
}

void Channel::setName(string name)
{
    m_name = name;
}

void Channel::setAdmin(int fd)
{
    m_admin = fd;
}

string Channel::getUserList(int newUserFd)
{
    string userList = "@";
    userList += m_userList[m_admin].getNick();

    map<int, User&>::iterator it = m_userList.begin();
    for (; it != m_userList.end(); ++it)
    {
        if (it->first != newUserFd && it->first != m_admin)
        {
            userList += " ";
            userList += it->second.getNick();
        }
    }
    return userList;
}