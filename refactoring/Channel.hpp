#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <string>
#include <vector>

#include "User.hpp"

using namespace std;

class Channel {
    private:
        map<string, vector<int> > m_channelList_string;
    public:
        bool isValidChannel(string channelName);
        void addChannel(string channelName);
        void addUser(string channelName, int fd);
        void deleteUser(string channelName, int fd);
        void setBroadCastMessage(string channelName, int sender, string message, User &user);
        string getUserList(User &user, string channelName, int fd);
        vector<int> getUserList_vec(string channelName);
        bool isAdmin(string channelName, int fd);
};


#endif