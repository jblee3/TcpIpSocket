#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int i;
    pid_t pid;

    if(argc != 2){
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    for(i=0; i<atoi(argv[1]); i++)
    {
        //printf(" Proc ID : %d,  i_val = %d \n", pid, i);
        pid=fork();
        printf(" Proc ID : %d,  i_val = %d \n", pid, i);
    }

    return 0;
}
