#include "command.hpp"
#include <iostream>

void join(User &user, Channel &channel, string target, int fd){

    vector<string> channelNames = split(target, ","); // 채널이 a,b,c,d로 들어온 경우 처리

    for (size_t i = 0; i < channelNames.size(); ++i)
    {
        string channelName = i == 0 ? channelNames[i] : "#" + channelNames[i];

        if (!channel.isValidChannel(channelName))
            channel.addChannel(channelName);

        if (channel.hasUser(channelName, fd)) // 채널에 이미 가입해 있는 경우는 거름
            continue;
        
        channel.addUser(channelName, fd);
        user.addChannel(fd, channelName);

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
}

void privmsg(User &user, Channel &channel, vector<string> command, int fd){

    string target = command[1];
    string message = command[2];
    string senderNickName = user.getNickName(fd);
    string senderLoginName = user.getLoginName(fd);
    string senderHostName = user.getHostName(fd);
    string fullMessage = prefixMessage(senderNickName, senderLoginName, senderHostName, command[0], target + " " + message);
    
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
    user.deleteChannel(fd, channelName);

    vector<int> userList =  channel.getUserList_vec(channelName);

    for (size_t i = 0; i < userList.size(); ++i)
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
    
    user.setBroadCastMessageToAllUser(fullMessage);
    user.setNickName(fd, newNickName);
}

void kick(User &user, Channel &channel, vector<string> command, int fd)
{
    string channelName = command[1];
    string target = command[2];
    string shortMessage = command.size() == 4 ? command[3] : "";

    string clientNickName = user.getNickName(fd);
    string clientLoginName = user.getLoginName(fd);
    string clientHostName = user.getHostName(fd);
    string message;

    if (channel.isAdmin(channelName, fd) && user.isExistUser(target))
    {
        message = prefixMessage(clientNickName, clientLoginName, clientHostName, "kick", channelName + " " + target + " " + shortMessage);
        channel.setBroadCastMessage(channelName, 0, message, user);
        channel.deleteUser(channelName, user.getUserFd(target));
        user.deleteChannel(user.getUserFd(target), channelName);
        if (user.getUserFd(target) == fd)
        {
            vector<int> userList =  channel.getUserList_vec(channelName);
            for (size_t i = 0; i < userList.size(); ++i)
            {
                int currentUser = userList[i];
                string fullDiffMessage = serverMessage(353, user.getNickName(currentUser), user.getLoginName(currentUser), \
                    channelName, channel.getUserList(user, channelName, currentUser));
                user.setWriteBuffer(currentUser, fullDiffMessage);
            }
        }
        return ;
    }
    if (channel.isAdmin(channelName, fd))
        message = serverMessage(401, clientNickName, clientLoginName, "" , "No such nick/channel");
    else
        message = serverMessage(481, clientNickName, clientLoginName, "" , "Permission Denied- You're not an IRC operator");
    user.setWriteBuffer(fd, message);
}

void quit(User &user, Channel &channel, string message, int fd){
    
    string fullMessage = prefixMessage(user.getNickName(fd), user.getLoginName(fd), user.getHostName(fd), "quit", message);
    vector<string> channelList = user.getChannelList(fd);
    vector<string>::iterator it = channelList.begin();

    for (; it != channelList.end(); ++it){
        vector<string> command;
        command.push_back("PART");
        command.push_back(*it);
        command.push_back(message);
        part(user, channel, command, fd);
    }

    user.setStatus(fd, QUIT);
    user.setWriteBuffer(fd, fullMessage);
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
    if (code == 353) {
        result += "= ";
    } else {
        result += " ";
    }
    result += channelName;
    result += " :";
    result += message;
    result += "\r\n";
    return result;
}

vector<string> split(string str, string delim) // ""
{
    vector<string> ret;
    int delim_len = delim.size();
    size_t cut;
    while ((cut = str.find(delim)) != string::npos)
    {
        if (str[0] == ':')
        {
            break;
        }
        string word = str.substr(0, cut);
        ret.push_back(word);
        str = str.substr(cut + delim_len);
    }
    if (str != "")
        ret.push_back(str);
    return ret;
}