#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <poll.h>

#define BUF_SIZE 100
void error_handling(char *buf);

int main(int argc, char *argv[]) {
    int theNumberOfFDs = 100;
    int serv_sock, clnt_sock;
    struct sockaddr_in serv_adr, clnt_adr;
    struct timeval timeout;
    // 파일 상태 테이블 선언
    // fd_set reads, cpy_reads;
    struct pollfd pollFDs[theNumberOfFDs];


    socklen_t adr_sz;
    int fd_max, str_len, fd_num, i;
    char buf[BUF_SIZE];
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

    // FD_ZERO(&reads); // fd_set 테이블을 초기화한다.
    // FD_SET(serv_sock, &reads); // 서버 소켓(리스닝 소켓)의 이벤트 검사를 위해 fd_set 테이블에 추가한다.
    fd_max = serv_sock;

    pollFDs[0].fd = serv_sock; // 0번째 배열에는 listen을 지정
    pollFDs[0].events = POLLIN; // 읽도록 만든다.
    pollFDs[0].revents = 0; // 처음에는 0으로 초기화 한다(아직 아무 일도 일어나지 않았으니)

    for (i = 1; i < theNumberOfFDs; i++)
      pollFDs[i].fd = -1; // 0번째 배열은 listen을 위한것이니 1번째부터 모두 -1로 초기화

    while(1) {
        // cpy_reads = reads;
        // 타임아웃 설정
        timeout.tv_sec = 5;
        timeout.tv_usec = 5000;

        // result
        // -1: 오류 발생
        // 0: 타임 아웃
        // 1 이상 : 등록된 파일 디스크립터에 해당 이벤트가 발생하면 이벤트가 발생한 파일 디스크립터의 수를 반환한다.
        if ((fd_num = poll(pollFDs, theNumberOfFDs, 5000)) == -1)
            break;

        if (fd_num == 0)
            continue;

        if (pollFDs[0].revents == POLLIN) {
            // 서버 소켓(리스닝 소켓)에 이벤트(연결 요청) 발생
            adr_sz = sizeof(clnt_adr);
            clnt_sock= accept(serv_sock, (struct sockaddr*)&clnt_adr, &adr_sz);                    
            for (i = 1; i < theNumberOfFDs; i++) {
              if (pollFDs[i].fd == -1) {
                pollFDs[i].fd = clnt_sock;
                pollFDs[i].events = POLLIN;
                pollFDs[i].revents = 0;
                printf("connected client: %d \n", clnt_sock);
                break;
              }
            }
          }
                // 클라이언트와 연결된 소켓에 이벤트 발생
          for (i=1; i<fd_max+1; i++) {
            int n = pollFDs[i].revents;
            printf("n: %d \n", n);
            switch (n)
            {
            case 0: // 이벤트가 일어나지 않은 경우
              break;
            case 1:
                str_len = read(i, buf, BUF_SIZE);
                write(4, buf, str_len);    // echo!
                write(5, buf, str_len);    // echo!
            default:
              printf("revents: %d \n", pollFDs[i].revents);
              close(i);
              pollFDs[i].fd = -1;
              pollFDs[i].revents = 0;
              printf("closed client: %d \n", i);
              break;
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