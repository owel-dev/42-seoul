NAME			= ircserv
CXX				= c++
CXXFLAGS		= -Wall -Wextra -Werror -std=c++98

RM				= rm -rf
OBJDIR			= ./obj/
SRCS			= User.cpp Server.cpp Channel.cpp main.cpp\
				  commands/join.cpp commands/kick.cpp commands/nick.cpp commands/part.cpp commands/privmsg.cpp commands/quit.cpp commands/utils.cpp
						
					
OBJS_FILE		= $(SRCS:.cpp=.o)
OBJS			= $(addprefix $(OBJDIR), $(OBJS_FILE))

all:			objd_build	$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR)%.o : %.cpp
				$(CXX) $(CXXFLAGS) $< -c -o $@

objd_build		:
				mkdir -p $(OBJDIR)
				mkdir -p $(OBJDIR)/commands

clean:
				@$(RM) $(OBJDIR)
				@$(RM) $(OBJS)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re 

