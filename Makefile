all: c s

c:
	c++ client.cpp -o client
s:
	c++ kqueue_server.cpp -o server