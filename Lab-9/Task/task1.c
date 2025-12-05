#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_handler(int signo)
{
    if (signo == SIGUSR1)
        printf("received SIGUSR1\n");
    else if (signo == SIGKILL)
        printf("received SIGKILL (but this will never print)\n");
    else if (signo == SIGSTOP)
        printf("received SIGSTOP (but this will never print)\n");
}

int main(void)
{
    struct sigaction sa;
    sa.sa_flags = 0;                  
    sa.sa_handler = sig_handler;      
    sigemptyset(&sa.sa_mask);       

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
        printf("\ncan't catch SIGUSR1\n");

    if (sigaction(SIGKILL, &sa, NULL) == -1)
        printf("\ncan't catch SIGKILL (expected)\n");

    if (sigaction(SIGSTOP, &sa, NULL) == -1)
        printf("\ncan't catch SIGSTOP (expected)\n");

    while (1)
        sleep(1);

    return 0;
}

