#include "command.hpp"

void userCmd(User &user, vector<string> command, int fd) {

    string nickName = user.getNickName(fd);

    if (command.size() == 1) {
        user.setWriteBuffer(fd, serverMessage(ERR_NEEDMOREPARAMS, nickName, "", "", "Not enough parameters"));
        return;
    }

    user.setLoginName(fd, command[1]);
}