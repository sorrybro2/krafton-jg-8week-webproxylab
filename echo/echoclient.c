#include "csapp.h"


/* 
argc : 인자의 개수. 프로그램 이름까지 포함
argv : 문자열 배열 
argv[0] = 프로그램 이름, 
argv[1] = host
argv[2] = port
*/
int main(int argc, char **argv) 
{
    // clientfd : 클라이언트 프로세스가 들고 있는 소켓 FD(파일 디스크립터)
    int clientfd;
    // host : 서버 호스트명/주소 (예: "localhost:8080")
    // port : 한 줄짜리 텍스트를 담는 작업용 버퍼
    char *host, *port, buf[MAXLINE]; 
    rio_t rio;

    if (argc != 3){
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }
    host = argv[1];
    port = argv[2];

    // (클랴 - 서버) 요청한 것을 찾고 연결함 -> 연결 디스크립터
    clientfd = Open_clientfd(host, port); // 바로 sockaddr로 넘겨 sockaddr_storage로 감
    Rio_readinitb(&rio, clientfd); // 버퍼드 읽기 상태를 fd에 붙여두는 초기화

    // 한 줄 입력 -> 서버에 보냄 -> 서버 응답 한 줄 받음 -> 출력
    while (Fgets(buf, MAXLINE, stdin) != NULL){ // 표준 입력에서 한 줄 (개행 포함)을 읽어 buf에 담음
        Rio_writen(clientfd, buf, strlen(buf)); // 1. 입력 라인을 서버 "끝까지" 전송
        Rio_readlineb(&rio, buf, MAXLINE); // 2. 서버 응답 한 줄을 받아 buf에 채움
        Fputs(buf, stdout); // 3. 클라이언트 터미널 화면에 출력
    }
    Close(clientfd); // 파일 디스크립터를 닫고 커널 자원을 변환
    exit(0);
}