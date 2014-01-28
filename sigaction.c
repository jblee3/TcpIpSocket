#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if(sig == SIGALRM)
        puts("Time out!");
    alarm(2);
}

void keycontrol(int sig)
{
    if(sig == SIGINT)
        puts("CTRL+C Pressed");
}

int main(int argc, char *argv[])
{
    int i;
    struct sigaction act;
    act.sa_handler=timeout;
    sigemptyset(&act.sa_mask);
    act.sa_flags=0;

    struct sigaction act2;
    act2.sa_handler=keycontrol;
    sigemptyset(&act2.sa_mask);
    act2.sa_flags=0;

    sigaction(SIGALRM, &act, 0);
    sigaction(SIGINT, &act2, 0);
    alarm(2);

    for(i=0; i<3; i++)
    {
        puts("wait...");
        sleep(100);
    }
    return 0;
}
