#ifndef DEFINE_HPP
#define DEFINE_HPP

#define RPL_WELCOME 001
#define RPL_YOURHOST 002
#define RPL_CREATED 003
#define RPL_MYINFO 004 
#define RPL_TOPIC 332
#define RPL_NAMREPLY 353
#define RPL_ENDOFNAMES 366 

///////////// error code

#define ERR_NOSUCHNICK 401      // 닉네임을 아무도 안쓰고 있을 때. // o
#define ERR_NEEDMOREPARAMS 461  // 커맨드 인자갯수 부족할때. // 구현해야 함
#define ERR_PASSWDMISMATCH 464  // 비밀번호 안넣었거나 틀렸을때. // 구현해야 함
#define ERR_NONICKNAMEGIVEN 431 // 닉 다음 인자를 안줬을경우. // 구현해야 함
#define ERR_ERRONEUSNICKNAME 432 // 닉에 이상한거 들어온경우 // 구현해야 함
#define ERR_NICKNAMEINUSE 433    // 닉네임 중복 // o
#define ERR_NOTREGISTERED 451    // 등록 안된 상태일때 // 구현해야 함
#define ERR_BADCHANMASK 476      // 채널에 #이 안붙었을때. // 구현해야 함
#define ERR_NOSUCHCHANNEL 403 // 구현해야 함
#define ERR_NORECIPIENT 411 // 구현해야 함
#define ERR_NOTEXTTOSEND 412 // 구현해야 함
#define ERR_UNKNOWNCOMMAND 421 // 구현해야 함
#define ERR_NOPRIVILEGES 481 // o
#define ERR_ALREADYREGISTRED 462
#define ERR_NOTONCHANNEL 442
#define ERR_CANNOTSENDTOCHAN 404

#endif