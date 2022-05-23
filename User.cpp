#include "User.hpp"

User::User(int fd) : m_fd(fd), m_status(0), m_nickName(""), m_loginName(""), m_hostName(""), m_password(""), m_writeBuffer("")
{
}

bool User::isChecked()
{
    return (m_nickName != "" && m_loginName != "" && m_password != "");
}

int User::getFd()
{
    return m_fd;
}

void User::setFd(int fd)
{
    m_fd = fd;
}

string User::getNick()
{
    return m_nickName;
}

void User::setNick(string nick)
{
    m_nickName = nick;
}

string User::getUserInfo()
{
    return m_loginName;
}

void User::setLoginName(string userInfo)
{
    m_loginName = userInfo;
}

string User::getPassword()
{
    return m_password;
}

void User::setPassword(string password)
{
    m_password = password;
}

string User::getChannelName()
{
    return m_channelName;
}

void User::setChannelName(string channelName)
{
    m_channelName = channelName;
}

string User::getWriteBuffer()
{
    return m_writeBuffer;
}

void User::setWriteBuffer(string newString)
{
    m_writeBuffer += newString;
}

void User::clearWriteBuffer()
{
    m_writeBuffer = "";
}

string User::getHostName()
{
    return m_hostName;
}

void User::setHostName(string hostName)
{
    m_hostName = hostName;
}

int User::getStatus()
{
    return m_status; 
}

void User::setStatus(int status)
{
    m_status = status;
}