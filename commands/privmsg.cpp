#include "command.hpp"

void privmsg(User &user, Channel &channel, vector<string> command, int fd){

    string target = command[1];
    string message = command[2];
    string senderNickName = user.getNickName(fd);
    string senderLoginName = user.getLoginName(fd);
    string senderHostName = user.getHostName(fd);
    string fullMessage = prefixMessage(senderNickName, senderLoginName, senderHostName, command[0], target + " " + message);
    
    if (target == "") {
        user.setWriteBuffer(fd, serverMessage(ERR_NORECIPIENT, senderNickName, "", "", "No recipient given " + command[0]));
        return;
    }
    if (message == "") {
        user.setWriteBuffer(fd, serverMessage(ERR_NOTEXTTOSEND, senderNickName, "", "", "No text to send"));
        return;
    }

    if (target[0] == '#'){
        if (!channel.isValidChannel(target)) {
            user.setWriteBuffer(fd, serverMessage(ERR_NOSUCHCHANNEL, senderNickName, target, "", "No such channel"));
            return;
        }
        channel.setBroadCastMessage(target, fd, fullMessage, user);
    }
    else {
        int receiver = user.getUserFd(target);
        user.setWriteBuffer(receiver, fullMessage);
    }
}