#include "command.hpp"

void part(User &user, Channel &channel, vector<string> command, int fd){

    string channelName = command[1];
    string message = command[2];
    string senderNickName = user.getNickName(fd);
    string senderLoginName = user.getLoginName(fd);
    string senderHostName = user.getHostName(fd);
    string fullMessage = prefixMessage(senderNickName, senderLoginName, senderHostName, "part", channelName + " " + message);

    if (channelName == "") {
        user.setWriteBuffer(fd, serverMessage(ERR_NEEDMOREPARAMS, senderNickName, "", "", "Not enough parameters"));
        return;
    }

    if (!channel.isValidChannel(channelName)) {
        user.setWriteBuffer(fd, serverMessage(ERR_NOSUCHCHANNEL, senderNickName, channelName, "", "No such channel"));
        return;
    }

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
