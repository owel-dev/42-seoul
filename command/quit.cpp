#include "../Server.hpp"

void Server::quit(std::vector<string> command, struct kevent event)
{
    int userFd = event.ident;
    
    // 채널의 유저리스트에서 해당 유저 삭제
    // 채널목록에서 채널을 돌면서 유저리스트에 해당 유저가 있는지 체크
    std::cout << "line 9" << std::endl;
    map<string, Channel>::iterator it = m_channelList.begin();
    for (;it != m_channelList.end(); ++it) {
        Channel &channel = it->second;
        if (channel.m_userList.count(userFd)) { // 있으면 erase로 삭제
            channel.m_userList.erase(userFd); 
        }
    }
    std::cout << "line 17" << std::endl;


    User &user = m_userList[userFd];
    std::cout << "line 21" << std::endl;

    user.setStatus(QUIT);
    user.setWriteBuffer(prefixMessage(user.getNick(), user.getUserInfo(), user.getHostName(), "quit", command[1]));
}

void Server::deleteUser(int i)
{
    vector<struct kevent>::iterator it = m_watchList.begin();
    for (;it != m_watchList.end(); ++it)
    {
        if (it->ident == m_eventList[i].ident) {
            m_watchList.erase(it);
            break;
        }
    }
    m_userList.erase(m_eventList[i].ident);
    close(m_eventList[i].ident);
}
