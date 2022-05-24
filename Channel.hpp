#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <utility>
#include <iostream>
#include <vector>
#include <map>
#include "User.hpp"


using namespace std;

class Channel
{
public:
    Channel();

    map<int, User&> m_userList;
    string m_name;
    int m_admin;

    void addUser(User &user);

    void setName(string name);

    void setAdmin(int fd);

    string getUserList(int newUserFd);
};

#endif