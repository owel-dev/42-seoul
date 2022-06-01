#include "command.hpp"

void nick(User &user, vector<string> command, int fd){

    string newNickName = command.size() > 1 ? command[1] : "";
    string nickName = user.getNickName(fd);
    string loginName = user.getLoginName(fd);
    string hostName = user.getHostName(fd);
    string fullMessage = prefixMessage(nickName, loginName, hostName, "NICK", newNickName);

    if (newNickName == "" || newNickName == ":"){
        user.setWriteBuffer(fd, serverMessage(ERR_NONICKNAMEGIVEN, nickName, "", "", "No nickname given"));
        return;
    }
    if (isValidNickName(newNickName) == false)
    {
        user.setWriteBuffer(fd, serverMessage(ERR_ERRONEUSNICKNAME, nickName, newNickName, "", "Erroneous nickname"));
        return;
    }
    if (user.isExistUser(newNickName))
    {
        user.setWriteBuffer(fd, serverMessage(ERR_NICKNAMEINUSE, nickName, newNickName, "", "Nickname is already in use"));
        return;
    }
    
    user.setNickName(fd, newNickName);
    
    if (user.isLogin(fd))
        user.setBroadCastMessageToAllUser(fullMessage);
}

bool isValidNickName(string newNickName)
{
    size_t len = newNickName.length();
    for (size_t i = 0; i < len; i++)
    {
        if (!(newNickName[i]  >= 65 && newNickName[i] <= 126) && !(newNickName[i]  >= 48 && newNickName[i] <= 57))
            return (false);
    }
    return (true);
}
