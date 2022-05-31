#include "command.hpp"

string prefixMessage(string nickName, string loginName, string hostName, string command, string message)
{
    string result = ":";
    result += nickName;
    result += "!";
    result += loginName;
    result += "@";
    result += hostName;
    result += " ";
    result += command;
    result += " ";
    result += message;
    result += "\r\n";
    return result;
}

string serverMessage(int code, string nickName, string loginName, string channelName, string message)
{
    string result = "";
    result += ":ft_irc.com ";
    result += to_string(code);
    result += " ";
    result += nickName;
    result += " ";
    result += loginName;
    if (code == 353) {
        result += "= ";
    } else {
        result += " ";
    }
    result += channelName;
    result += " :";
    result += message;
    result += "\r\n";
    return result;
}

vector<string> split(string str, string delim) // ""
{
    vector<string> ret;
    int delim_len = delim.size();
    size_t cut;
    while ((cut = str.find(delim)) != string::npos)
    {
        if (str[0] == ':')
        {
            break;
        }
        string word = str.substr(0, cut);
        ret.push_back(word);
        str = str.substr(cut + delim_len);
    }
    if (str != "")
        ret.push_back(str);
    return ret;
}