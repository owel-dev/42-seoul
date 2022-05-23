#include "../Server.hpp"

void Server::part(std::vector<string> command, struct kevent event)
{
    
    // 해당 채널의 유저 목록을 돌면서 메시지 전송
    string channelName = command[1];
    string message = command[2];
    Channel &channel = m_channelList[channelName];
    map<int, User>::iterator it = channel.m_userList.begin();
    User &sender = m_userList[event.ident];
    string msg = channelName + " " + message;
    for (;it != channel.m_userList.end(); ++it)
    {
        User &receiver = it->second;
        m_userList[receiver.getFd()].setWriteBuffer(prefixMessage(sender.getNick(), sender.getUserInfo(), sender.getHostName(), "part", msg));
    }
    channel.m_userList.erase(event.ident);
    // 채널 안에 사람이 한 명도 없는 경우 해당 채널 지우기
    if (channel.m_userList.size() == 0) {
        m_channelList.erase(channelName);
    }
    // 채널 안에 사람이 있으면서 방금 나간 사람이 어드민인 경우, 다음 사람으로 어드민 바꾸기
    else if (channel.m_admin == event.ident) {
        int firstFd = (channel.m_userList.begin())->second.getFd();
        channel.setAdmin(firstFd);
    }
    // 채팅방 유저 목록 업데이트
    for (it = channel.m_userList.begin(); it != channel.m_userList.end(); ++it)
    {
        User &receiver = it->second;
        m_userList[receiver.getFd()].setWriteBuffer(serverMessage(353, receiver.getNick(), receiver.getUserInfo(), channelName, channel.getUserList(receiver.getFd())));
    }
}