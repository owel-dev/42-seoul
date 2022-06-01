#include "command.hpp"

void pass(User &user, string serverPassword, vector<string> command, int fd) {
    string nickName = user.getNickName(fd);
    string userPassword = command[1];

    if (userPassword == "") {
        user.setWriteBuffer(fd, serverMessage(ERR_NEEDMOREPARAMS, nickName, "", "", "Not enough parameters"));
        return;
    }
    if (user.isLogin(fd)){
        user.setWriteBuffer(fd, serverMessage(ERR_ALREADYREGISTRED, nickName, "", "", "Unauthorized command (already registered)"));
        return;
    }
    if (userPassword != serverPassword){
        user.setWriteBuffer(fd, serverMessage(ERR_PASSWDMISMATCH, nickName, "", "", "Password incorrect"));
        return;
    }
    user.setPassword(fd, userPassword);
}