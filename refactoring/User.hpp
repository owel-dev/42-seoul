#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <map>

using namespace std;



class User {
    private:
        struct userInfo {
            string nickName;
            string loginName;
            string hostName;
            string password;
            string writeBuffer;

            userInfo()
            {
                nickName = "";
                loginName = "";
                hostName = "";
                password = "";
                writeBuffer = "";
            }
        };        
        map<int, struct userInfo> m_userList_int;
        map<string, int> m_userList_string;

    
    public:
        void addUser(int fd);
        string getNickName(int fd);
        void setNickName(int fd, string nickName);
        void setLoginName(int fd, string loginName);
        void setHostName(int fd, string hostname);
        void setPassword(int fd, string password);
        bool isLogin(int fd);
        void setWriteBuffer(int fd, string newString);
        string getWriteBuffer(int fd);
        void clearWriteBuffer(int fd);
        string getHostName(int fd);
        string getPassword(int fd);
        string getLoginName(int fd);
};      

#endif