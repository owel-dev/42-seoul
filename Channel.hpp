#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <utility>
#include <iostream>
#include <vector>
#include "Server.hpp"

using namespace std;


class Channel
{
    public:    
        map<int, User> m_userList;
        string m_name;
        int m_admin;
        
        void addUser(User user) {
            m_userList.insert(make_pair(user.m_fd, user));
        }

        void setName(string name) {
            m_name = name;
        }

        void setAdmin(int fd) {
            m_admin = fd;
        }

        string getUserList(int newUserFd) {
            string userList = "@";
            userList += m_userList[m_admin].get_nick();

            map<int, User>::iterator it = m_userList.begin();
            for (;it != m_userList.end(); ++it) {
                if (it->first != newUserFd && it->first != m_admin) {
                    userList += " ";
                    userList += it->second.get_nick();
                }
            }
            return userList;
        }
};

#endif