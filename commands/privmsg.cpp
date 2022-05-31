#include "command.hpp"

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