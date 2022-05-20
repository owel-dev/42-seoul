#include <iostream>

using namespace std;

class User
{
  private:

  public:
  int m_fd;
  string m_nickName; // nickName으로 
  string m_loginName;
  string m_realName;
  string m_password;
  string m_channelName;

  public:
  User(int fd = 0) : m_fd(fd), m_nickName(""), m_loginName(""), m_password("")
  {

  }

  bool isChecked()
  {
      return (m_nickName != "" && m_loginName != "" && m_password != "");
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

};