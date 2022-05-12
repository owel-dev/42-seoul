//
// Created by a_ulee on 2022/05/10.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <iostream>
#include <vector>

using namespace std;

void error_handling(string message)
{
  cerr << message << endl;
  exit(1);
}

int main(int argc, char *argv[])
{
  int serv_sock;
  int clnt_sock;

  struct sockaddr_in serv_addr;
  struct sockaddr_in clnt_addr;
  socklen_t clnt_addr_size;

  char message[] = "hello samin";

  if (argc != 2) {
    cout << "Usage : " << argv[0] << " <port>" << endl;
    exit(1);
  }

  // 소켓 생성
  serv_sock = socket(PF_INET, SOCK_STREAM, 0);
  if (serv_sock == -1)
    error_handling("socker() error");
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(atoi(argv[1]));

  // 소켓에 정보 할당
  if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
    error_handling("bind() error");

  // 수신 대기
  if (listen(serv_sock, 3) == -1)
    error_handling("listen() error");
  clnt_addr_size = sizeof(clnt_addr);

  vector<int> sockets;

  for (int i = 0; i < 3; ++i) {
    clnt_sock = accept(serv_sock, (struct sockaddr *) &clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1) {
      error_handling("accept() error");
      break;
    }
    sockets.push_back(clnt_sock);
    cout << "connect: " << i + 1 << endl;
  }
  for (vector<int>::iterator it = sockets.begin(); it != sockets.end(); ++it)
  {
    write(*it, message, sizeof(message));
  }

  close(clnt_sock);
  close(serv_sock);
  return 0;
}