#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    pid_t pid=fork();

    if(pid==0)
    {
        puts("Hi, I am a child process");
        sleep(20);
    }
    else
    {
        printf("Child Process ID: %d \n", pid);
        //sleep(30);
    }

    if(pid==0)
        printf("End child process");
    else
        printf("End parent process");

    return 0;
}
