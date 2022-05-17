#include <iostream>

using namespace std;

class User
{
  private:

  public:
  int m_fd;
  string m_nick;
  string m_userInfo;
  string m_password;
  string m_channelName;

  public:
  User(int fd = 0) : m_fd(fd), m_nick(""), m_userInfo(""), m_password("")
  {

  }

//  User(const User& x) : m_fd(x.m_fd), m_nick(x.m_nick), m_userInfo(x.m_userInfo), m_password(x.m_password) {
//
//  }

  bool isChecked()
  {
      return (m_nick != "" && m_userInfo != "" && m_password != "");
  }

  string get_nick()
  {
      return m_nick;
  }

  void set_nick(string nick)
  {
      m_nick = nick;
  }

  string get_userInfo()
  {
      return m_userInfo;
  }

  void set_userInfo(string userInfo)
  {
      m_userInfo = userInfo;
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

};