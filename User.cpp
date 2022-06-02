#include "User.hpp"

void User::addUserListInt(int fd){
    m_userList_int.insert(make_pair(fd, userInfo()));
}

void User::addUserListString(int fd, string nickName){
    m_userList_string.insert(make_pair(nickName, fd));
}

void User::setHostName(int fd, string hostname){
    m_userList_int[fd].hostName = hostname;
}

void User::setNickName(int fd, string nickName){
    m_userList_string.erase(m_userList_int[fd].nickName);
    addUserListString(fd, nickName);
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

void User::clearBuffer(int fd){
    m_userList_int[fd].writeBuffer = "";
    m_userList_int[fd].readBuffer = "";
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

int User::getUserFd(string nickName){
    return m_userList_string[nickName];
}

bool User::isExistUser(string nickName){
    return(m_userList_string.count(nickName));
}

void User::setBroadCastMessageToAllUser(string message){
    map<int, struct userInfo>::iterator it = m_userList_int.begin();

    for (; it != m_userList_int.end(); ++it){
        setWriteBuffer(it->first, message);
    }
}

void User::addChannel(int fd, string channelName){
    m_userList_int[fd].channelList.push_back(channelName);
}

vector<string> User::getChannelList(int fd){
    return m_userList_int[fd].channelList;
}

void User::deleteChannel(int fd, string channelName){
    
    vector<string> &channelList = m_userList_int[fd].channelList;
    vector<string>::iterator it = channelList.begin();
    
    for (; it != channelList.end(); ++it){
        if (*it == channelName){
            channelList.erase(it);
            break;
        }
    }
}

void User::deleteUser(int fd)
{
    string nickName = getNickName(fd);
    m_userList_int.erase(fd);
    m_userList_string.erase(nickName);
    close(fd);
}

int User::getStatus(int fd)
{
    return m_userList_int[fd].status;
}

void User::setStatus(int fd, int status)
{
    m_userList_int[fd].status = status;
}

map<string, int> User::getUserListString()
{
    return m_userList_string;
}

void User::setReadBuffer(int fd, string newString)
{
    m_userList_int[fd].readBuffer += newString;
}

string User::getReadBuffer(int fd)
{
    return m_userList_int[fd].readBuffer;
}
