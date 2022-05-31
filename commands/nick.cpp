#include "command.hpp"

void nick(User &user, string newNickName, int fd){

    string nickName = user.getNickName(fd);
    string loginName = user.getLoginName(fd);
    string hostName = user.getHostName(fd);
    string fullMessage = prefixMessage(nickName, loginName, hostName, "NICK", newNickName);

    if(user.isExistUser(newNickName))
    {
        user.setWriteBuffer(fd, serverMessage(ERR_NICKNAMEINUSE, nickName, "", "", "Nickname is already in use"));
        return;
    }
    
    user.setNickName(fd, newNickName);
    
    if (user.isLogin(fd))
        user.setBroadCastMessageToAllUser(fullMessage);
}