#ifndef USER_HPP
#define USER_HPP

#include <iostream>

using namespace std;

class User
{
  private:

  public:
  int m_fd;
  string m_nickName;
  string m_loginName;
  string m_hostName;
  string m_password;
  string m_channelName;
  string m_writeBuffer;

  public:
  User(int fd = 0) : m_fd(fd), m_nickName(""), m_loginName(""), m_hostName(""), m_password(""), m_writeBuffer("")
  {

  }

  bool isChecked()
  {
      return (m_nickName != "" && m_loginName != "" && m_password != "");
  }

  int getFd()
  {
      return m_fd;
  }

  void setFd(int fd)
  {
      m_fd = fd;
  }

  string get_nick()
  {
      return m_nickName;
  }

  void set_nick(string nick)
  {
      m_nickName = nick;
  }

  string get_userInfo()
  {
      return m_loginName;
  }

  void set_loginName(string userInfo)
  {
      m_loginName = userInfo;
  }

  string get_password()
  {
      return m_password;
  }

  void set_password(string password)
  {
      m_password = password;
  }

  string get_channelName()
  {
      return m_channelName;
  }

  void set_channelName(string channelName)
  {
      m_channelName = channelName;
  }

  string getWriteBuffer()
  {
      return m_writeBuffer;
  }

  void setWriteBuffer(string newString)
  {
    m_writeBuffer += newString;
  }

  void clearWriteBuffer()
  {
      m_writeBuffer = "";
  }

  string getHostName()
  {
      return m_hostName;
  }

  void setHostName(string hostName)
  {
      m_hostName = hostName;
  }
};

#endif