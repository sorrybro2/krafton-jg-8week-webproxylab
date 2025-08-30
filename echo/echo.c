#include "csapp.h"

void echo(int connfd)
{
    ssize_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd); // 버퍼 초기화
    while((n = Rio_readlineb(&rio, buf, MAXLINE))!=0){  // 줄 단위 읽기
        fprintf(stderr, "server received %d bytes\n", (int)n);    // 로그
        Rio_writen(connfd, buf, n);                     // 그대로 돌려줌
    }
}