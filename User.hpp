#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <map>
#include <vector>
#include <unistd.h>

#define QUIT 1

using namespace std;


class User {
    private:
        struct userInfo {
            string nickName;
            string loginName;
            string hostName;
            string password;
            string writeBuffer;
            string readBuffer;
            int status;
            vector<string> channelList;

            userInfo()
            {
                nickName = "";
                loginName = "";
                hostName = "";
                password = "";
                writeBuffer = "";
                status = 0;
            }
        };        
        map<int, struct userInfo> m_userList_int;
        map<string, int> m_userList_string;

    
    public:
        void addUserListInt(int fd);
        void addUserListString(int fd, string nickName);
        void addChannel(int fd, string channelName);
        string getNickName(int fd);
        void setNickName(int fd, string nickName);
        void setLoginName(int fd, string loginName);
        void setHostName(int fd, string hostname);
        void setPassword(int fd, string password);
        bool isLogin(int fd);
        void setWriteBuffer(int fd, string newString);
        string getWriteBuffer(int fd);
        void clearWriteBuffer(int fd);
        void clearReadBuffer(int fd);
        string getHostName(int fd);
        string getPassword(int fd);
        string getLoginName(int fd);
        int getUserFd(string nickName);
        bool isExistUser(string nickName);
        void setBroadCastMessageToAllUser(string command);
        vector<string> getChannelList(int fd);
        void deleteChannel(int fd, string channelName);
        void deleteUser(int fd);
        int getStatus(int fd);
        void setStatus(int fd, int status);
        map<string, int> getUserListString();
        void setReadBuffer(int fd, string newString);
        string getReadBuffer(int fd);
};      

#endif