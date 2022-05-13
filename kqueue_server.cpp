#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>
#include <vector>
#include <fcntl.h>
#include <iostream>

using namespace std;

#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char *argv[]) {
    int theNumberOfFDs = 100;
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;

    socklen_t adr_sz;
    int fd_max, str_len, fd_num, i;
    // char buf[BUF_SIZE];
    string buf[BUF_SIZE];
    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_adr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
        error_handling("bind() error");
    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    //********************************
    //1. kqueue 초기화  ****************
    //********************************

    int kq;
    if ((kq = kqueue()) == -1)// 새로운 kernel event queue를 생성하고 해당 디스크립터를 반환한다.
        printf("kqueue error\n"); // 에러가 나면 -1을 반환하고, 성공하면 kqueue의 디스크립터를 반환한다.

    struct kevent ChangeList[100]; // 추가하거나 바꿀 이벤트의 리스트
    int nChanges = 0; // Changelist의 수
    
    struct kevent EventList[100]; // 이벤트를 받으면 커널에서 이벤트를 넣어주는 배열

    //********************************
    //2. kevent 구조체 초기화  **********
    //********************************

    struct kevent temp_event;
    std::vector<struct kevent> addEvent;

    EV_SET(&temp_event, serv_sock, EVFILT_READ, EV_ADD|EV_ENABLE, 0, 0, NULL);
    addEvent.push_back(temp_event);

    //********************************
    //3.
    //********************************

    struct kevent eventList[100];
    struct kevent *currEvent;
    int user[10] = {};

    while (true) {
      std::cout << "while start" << std::endl;
      int eventCount = kevent(kq, &addEvent[0], addEvent.size(), eventList, 100, NULL);
      if (eventCount == -1) {
        printf("kevent error\n");
        break;
      }
      addEvent.clear();
      for (int i = 0; i < eventCount; i++) {
        currEvent = &eventList[i];
        if (currEvent->flags &EV_ERROR) 
          printf("EV_ERROR\n");
        else if (currEvent->filter == EVFILT_READ) {
          if (currEvent->ident == serv_sock) {
            adr_sz = sizeof(clnt_adr);
            clnt_sock= accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);  
            // fcntl(clnt_sock, F_SETFL, O_NONBLOCK);
	          EV_SET(&temp_event, clnt_sock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL);
            addEvent.push_back(temp_event);
	          // EV_SET(&temp_event, clnt_sock, EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, NULL);
            user[clnt_sock] = 1;
            printf("connect user %d\n", clnt_sock);
          } else {
            printf("READ\n");
            str_len = read(currEvent->ident, buf, BUF_SIZE);
            std::cout << "str_len: " << str_len <<  ", send to client: " << buf << std::endl;
            for (int i = 0; i < 100; i++) {
              if (user[i] == 1) {
                write(i, buf, str_len);
              }
            }
          }
        }
      }
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *buf) {
    fputs(buf, stderr);
    fputc('\n', stderr);
    exit(1);
}
