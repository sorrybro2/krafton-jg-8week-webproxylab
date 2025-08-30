#include "csapp.h"

void echo(int connfd);

int main(int argc, char **argv)
{
    /* listenfd : socket->bind->listen
       connfd : accept(listendf,..)가 새 연결마다 반환하는 연결 디스트립터 */
    int listenfd, connfd; 
    socklen_t clientlen; // accept()에 넘기는 주소 구조체 크기
    struct sockaddr_storage clientaddr; // 클라이언트의 소켓 주소를 담는 그릇
    char client_hostname[MAXLINE], client_port[MAXLINE]; //클라이언트의 host, port

    if (argc != 2){
        fprintf(stderr, "usage : %s <port>\n", argv[0]);
        exit(0);
    }

    // 연결 디스크럽트 직전인 듣기 디스크럽트까지 만들어놓는 함수
    listenfd = Open_listenfd(argv[1]);

    while(1) {
        clientlen = sizeof(struct sockaddr_storage);

        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); // 성공 시 연결 디스크립터로 반환
        // Accept()가 채운 cilentaddr(클라이언트 소켓 주소)를 Getnameinto() 가 문자열로 변환해서 그 버퍼를 복사해서 넣는 작업
        Getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE, client_port, MAXLINE, 0); 

        printf("Connected to (%s, %s)\n", client_hostname, client_port);
        echo(connfd);
        Close(connfd); // 파일 디스크립터를 닫고 커널 자원을 변환
    }

}