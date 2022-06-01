#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include "../define.hpp"
#include "../User.hpp"
#include "../Channel.hpp"

void join(User &user, Channel &channel, string target, int fd);
void privmsg(User &user, Channel &channel, vector<string> command, int fd);
void part(User &user, Channel &channel, vector<string> command, int fd);

void nick(User &user, string newNickName, int fd);
bool isValidNickName(string newNickName);

void userCmd(User &user, vector<string> command, int fd);
void pass(User &user, string serverPassword, vector<string> command, int fd);
void kick(User &user, Channel &channel, vector<string> command, int fd);
void quit(User &user, Channel &channel, string message, int fd);
void deleteUser(User &user, int fd);

string serverMessage(int code, string nickName, string loginName, string channelName, string message);
string prefixMessage(string nickName, string loginName, string hostName, string command, string message);
vector<string> split(string str, string delim);

#endif