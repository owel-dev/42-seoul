#include "command.hpp"
#include <iostream>

void join(User &user, Channel &channel, string channelName, int fd){

    if (!channel.isValidChannel(channelName)) {
        channel.addChannel(channelName);
    } 

    channel.addUser(channelName, fd);

    string nickName = user.getNickName(fd);
    string loginName = user.getLoginName(fd);
    string hostName = user.getHostName(fd);
    string message = prefixMessage(nickName, loginName, hostName, "JOIN", channelName);
    
    channel.setBroadCastMessage(channelName, 0, message, user);
    user.setWriteBuffer(fd, serverMessage(332, nickName, loginName, channelName, "A timey-wimey channel"));
    user.setWriteBuffer(fd, serverMessage(353, nickName, loginName, channelName, \
        channel.getUserList(user, channelName, fd)));
    user.setWriteBuffer(fd, serverMessage(366, nickName, loginName, channelName, "End of NAMES list"));
}

void privmsg(User &user, Channel &channel, vector<string> command, int fd){

    string target = command[1];
    string message = command[2];
    string senderNickName = user.getNickName(fd);
    string senderLoginName = user.getLoginName(fd);
    string senderHostName = user.getHostName(fd);
    string fullMessage = prefixMessage(senderNickName, senderLoginName, senderHostName, "privmsg", target + " " + message);
    
    if (target[0] == '#'){
        channel.setBroadCastMessage(target, fd, fullMessage, user);
    }
    else {
        int receiver = user.getUserFd(target);
        user.setWriteBuffer(receiver, fullMessage);
    }
}

void part(User &user, Channel &channel, vector<string> command, int fd){

    string channelName = command[1];
    string message = command[2];
    string senderNickName = user.getNickName(fd);
    string senderLoginName = user.getLoginName(fd);
    string senderHostName = user.getHostName(fd);
    string fullMessage = prefixMessage(senderNickName, senderLoginName, senderHostName, "part", channelName + " " + message);

    channel.setBroadCastMessage(channelName, 0, fullMessage, user);
    
    channel.deleteUser(channelName, fd);

    vector<int> userList =  channel.getUserList_vec(channelName);
    for (int i = 0; i < userList.size(); ++i)
    {
        int currentUser = userList[i];
        string fullDiffMessage = serverMessage(353, user.getNickName(currentUser), user.getLoginName(currentUser), \
            channelName, channel.getUserList(user, channelName, currentUser));
        user.setWriteBuffer(currentUser, fullDiffMessage);
    }
}

void nick(User &user, string newNickName, int fd){

    string nickName = user.getNickName(fd);
    string loginName = user.getLoginName(fd);
    string hostName = user.getHostName(fd);
    string fullMessage = prefixMessage(nickName, loginName, hostName, "NICK", newNickName);

    if(user.isExistUser(newNickName))
    {
        user.setWriteBuffer(fd, serverMessage(433, nickName, loginName, "", "Nickname is already in use"));
        return;
    }
    
    user.setBroadCastMessageToAllUser(user, fullMessage);
    user.setNickName(fd, newNickName);
}



string prefixMessage(string nickName, string loginName, string hostName, string command, string message)
{
    string result = ":";
    result += nickName;
    result += "!";
    result += loginName;
    result += "@";
    result += hostName;
    result += " ";
    result += command;
    result += " ";
    result += message;
    result += "\r\n";
    return result;
}

string serverMessage(int code, string nickName, string loginName, string channelName, string message)
{
    string result = "";
    result += ":ft_irc.com ";
    result += to_string(code);
    result += " ";
    result += nickName;
    result += " ";
    result += loginName;
    if (code == 332 || code == 366) {
        result += " ";
    } else {
        result += "= ";
    }
    result += channelName;
    result += " :";
    result += message;
    result += "\r\n";
    return result;
}