all: c s

c:
	c++ client.cpp -o client
s:
	c++ server.cpp -o server
