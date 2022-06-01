#include "command.hpp"

void kick(User &user, Channel &channel, vector<string> command, int fd)
{
    string channelName = command[1];
    string target = command[2];
    string shortMessage = command.size() == 4 ? command[3] : "";
    string clientNickName = user.getNickName(fd);
    string clientLoginName = user.getLoginName(fd);
    string clientHostName = user.getHostName(fd);
    string message;
    
    // if (command.size() < 3) {
    //     user.setWriteBuffer(fd, serverMessage(ERR_NEEDMOREPARAMS, clientNickName, "", "", "Not enough parameters"));
    //     return;
    // }

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
        message = serverMessage(ERR_NOSUCHNICK, clientNickName, clientLoginName, "" , "No such nick/channel");
    else
        message = serverMessage(ERR_NOPRIVILEGES, clientNickName, clientLoginName, "" , "Permission Denied- You're not an IRC operator");
    user.setWriteBuffer(fd, message);
}