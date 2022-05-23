all: s

s:
	c++ User.cpp Channel.cpp Server.cpp main.cpp command/*.cpp -o server