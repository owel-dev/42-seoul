all: c s

c:
	c++ client.cpp -o client
s:
	c++ main.cpp -o server