#ifndef USER_HPP
#define USER_HPP

#include <iostream>

using namespace std;

class User
{
  public:
  int m_fd;
  string m_nickName;
  string m_loginName;
  string m_hostName;
  string m_password;
  string m_channelName;
  string m_writeBuffer;

  public:
  User(int fd = 0);

  bool isChecked();

  int getFd();

  void setFd(int fd);

  string getNick();

  void setNick(string nick);

  string getUserInfo();

  void setLoginName(string userInfo);

  string getPassword();

  void setPassword(string password);

  string getChannelName();

  void setChannelName(string channelName);

  string getWriteBuffer();

  void setWriteBuffer(string newString);

  void clearWriteBuffer();

  string getHostName();

  void setHostName(string hostName);
};

#endif