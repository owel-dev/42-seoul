#include <iostream>
#include <vector>

using namespace std;

class Channel
{
    public:    
        vector<int> m_userList;
        string m_name;
        
        void addUser(int fd) {
            m_userList.push_back(fd);
        }

        void setName(string name) {
            m_name = name;
        }
};