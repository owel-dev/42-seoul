#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "User.hpp"
#include "Channel.hpp"

void join(User &user, Channel &channel, string channelName, int fd);
void privmsg(User &user, Channel &channel, vector<string> command, int fd);
void part(User &user, Channel &channel, vector<string> command, int fd);
void nick(User &user, string newNickName, int fd);

string serverMessage(int code, string nickName, string loginName, string channelName, string message);
string prefixMessage(string nickName, string loginName, string hostName, string command, string message);

#endif