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

using namespace std;

void error_handling(string message)
{
  cerr << message << endl;
  exit(1);
}

int main(int argc, char *argv[])
{
  int sock;
  struct sockaddr_in serv_addr;
  char message[30];
  int str_len;

  if (argc < 3) {
    cout << "Usage : " << argv[0] << " <port>" << endl;
    exit(1);
  }

  sock = socket(PF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    error_handling("sock() error");
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
  serv_addr.sin_port = htons(atoi(argv[2]));

  if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
    error_handling("connect error()");
  while (1) {
    if (argc == 4) {
      send(sock, argv[3], sizeof(argv[3]), 0);
    }
    str_len = recv(sock, message, sizeof(message) - 1, 0);
    if (str_len == -1)
      error_handling("read() error");
    cout << "message from server : " << message << endl;
  }
  // char *msg = argv[3];
  // send(sock, msg, sizeof(msg), 0);
  // str_len = recv(sock, message, sizeof(message) - 1, 0);
  // if (str_len == -1)
  //   error_handling("read() error");
  // cout << "message from server : " << message << endl;
  close(sock);
  return 0;
}