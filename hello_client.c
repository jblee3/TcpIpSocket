#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
void error_handling(char *messege);

int main(int argc, char *argv[]){
    int sock;

    struct sockaddr_in serv_addr;
    char messege[30];
    int str_len;

    if(argc != 3){
        printf("Usage : %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    str_len = read(sock, messege, sizeof(messege)-1);
    if(str_len == -1)
        error_handling("read() error");

    printf("Messege form server : %s \n", messege);
    close(sock);
    return 0;
}

void error_handling(char *messege){
    fputs(messege, stderr);
    fputc('\n', stderr);
    exit(1);
}

