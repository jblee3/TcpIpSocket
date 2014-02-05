#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_routine(int sock, char* message);
void write_routine(int sock, char* message);

int main(int argc, char *argv[]){
    int sock;
    pid_t pid;
    char message[BUF_SIZE];
    struct sockaddr_in serv_addr;

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
    else
        puts("Connected ........");

    pid = fork();
    if(pid == 0)
        write_routine(sock, message);
    else
        read_routine(sock, message);

    close(sock);
    return 0;
}

void read_routine(int sock, char *message)
{
    while(1)
    {
        int str_len = read(sock, message, BUF_SIZE);
        //if(str_len == -1)
        //    error_handling("read() error");
        if(str_len == 0)
            return ;

        message[str_len] = 0;
        printf("Message form server : %s \n", message);
    }
}

void write_routine(int sock, char *message)
{
    while(1)
    {
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n"))
        {
            shutdown(sock, SHUT_WR);
            return ;
        }
        write(sock, message, strlen(message));
    }
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

