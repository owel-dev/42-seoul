#include "User.hpp"

void User::addUser(int fd){
    m_userList_int.insert(make_pair(fd, userInfo()));
}

void User::setHostName(int fd, string hostname){
    m_userList_int[fd].hostName = hostname;
}

void User::setNickName(int fd, string nickName){
    m_userList_int[fd].nickName = nickName;
}

void User::setPassword(int fd, string password){
    m_userList_int[fd].password = password;
}

void User::setLoginName(int fd, string loginName){
    m_userList_int[fd].loginName = loginName;
}

string User::getNickName(int fd){
    return m_userList_int[fd].nickName;
}
// map<int, struct userInfo> getUserList(int fd)
// {
    
// }

// map<int, struct userInfo> getUserList_int(int fd)
// {

// }

bool User::isLogin(int fd){
    return m_userList_int[fd].hostName != "" && \
    m_userList_int[fd].loginName != "" && \
    m_userList_int[fd].nickName != "" && \
    m_userList_int[fd].password != "";
}

void User::setWriteBuffer(int fd, string newString)
{
    m_userList_int[fd].writeBuffer += newString;
}

string User::getWriteBuffer(int fd){
    return m_userList_int[fd].writeBuffer;
}

void User::clearWriteBuffer(int fd){
    m_userList_int[fd].writeBuffer = "";
}

string User::getHostName(int fd){
    return m_userList_int[fd].hostName;
}

string User::getPassword(int fd){
    return m_userList_int[fd].password;
}

string User::getLoginName(int fd){
    return m_userList_int[fd].loginName;
}