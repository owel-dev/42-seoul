#include "Channel.hpp"
#include <iostream>

bool Channel::isValidChannel(string channelName){
    return m_channelList_string.count(channelName);
}

void Channel::addChannel(string channelName){
    m_channelList_string.insert(make_pair(channelName, vector<int>()));
}

void Channel::addUser(string channelName, int fd){
    m_channelList_string[channelName].push_back(fd);
}

void Channel::deleteUser(string channelName, int fd){

    if (m_channelList_string[channelName].size() == 1){
        m_channelList_string.erase(channelName);
        return;
    }
    vector<int>::iterator it = m_channelList_string[channelName].begin();
    for (; it != m_channelList_string[channelName].end(); ++it){
        if (*it == fd) {
            m_channelList_string[channelName].erase(it);
            break;
        }
    }
}

void Channel::setBroadCastMessage(string channelName, int sender, string message, User &user){
    vector<int>::iterator it = m_channelList_string[channelName].begin();

    for (; it != m_channelList_string[channelName].end(); ++it){
        if (sender != *it){
            user.setWriteBuffer(*it, message);
        }
    }
}

string Channel::getUserList(User &user, string channelName, int fd){
    
    string userList = "@";
    int admin = *(m_channelList_string[channelName].begin());
    userList += user.getNickName(admin);

    vector<int>::iterator it = m_channelList_string[channelName].begin();
    for (; it != m_channelList_string[channelName].end(); ++it)
    {
        if (*it != fd && it != m_channelList_string[channelName].begin())
        {
            userList += " ";
            userList += user.getNickName(*it);
        }
    }
    return userList;
}

vector<int> Channel::getUserList_vec(string channelName){
    return m_channelList_string[channelName];
}
