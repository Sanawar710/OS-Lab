// Task_4(B).c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY_B 5678

int main()
{
    int shmidB = shmget(SHM_KEY_B, sizeof(int), IPC_CREAT | 0666);
    if (shmidB < 0)
    {
        perror("shmget B");
        exit(1);
    }

    int *b = (int *)shmat(shmidB, NULL, 0);
    if (b == (void *)-1)
    {
        perror("shmat B");
        exit(1);
    }

    *b = 1; // Initialize B to 1
    printf("Writer B: initialized shared memory B = %d\n", *b);

    shmdt(b);

    return 0;
}
