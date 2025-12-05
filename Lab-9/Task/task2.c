#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    // Try to ignore SIGKILL
    if (signal(SIGKILL, SIG_IGN) == SIG_ERR)
        printf("Cannot ignore SIGKILL (expected)\n");

    // Try to ignore SIGSTOP
    if (signal(SIGSTOP, SIG_IGN) == SIG_ERR)
        printf("Cannot ignore SIGSTOP (expected)\n");

    printf("Program running... Try sending SIGKILL or SIGSTOP.\n");

    while (1) {
        sleep(1);
    }

    return 0;
}

