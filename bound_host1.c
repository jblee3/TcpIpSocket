#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]){
    int serv_sock;
    char message[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in my_addr;
    struct sockaddr_in your_addr;
    socklen_t your_addr_size;

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(serv_sock == -1)
        error_handling("UDP socket() error");

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &my_addr, sizeof(my_addr)) == -1)
        error_handling("bind() error");

    for(i=0; i<3; i++)
    {
        sleep(5);
        your_addr_size = sizeof(your_addr);
        str_len = recvfrom(serv_sock, message, BUF_SIZE, 0,
                    (struct sockaddr*)&your_addr, &your_addr_size);

        printf("Message %d: %s \n", i+1, message);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

