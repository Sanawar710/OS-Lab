// Task-4_A.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY_A 1234

int main()
{
    int shmidA = shmget(SHM_KEY_A, sizeof(int), IPC_CREAT | 0666);
    if (shmidA < 0)
    {
        perror("shmget A");
        exit(1);
    }

    int *a = (int *)shmat(shmidA, NULL, 0);
    if (a == (void *)-1)
    {
        perror("shmat A");
        exit(1);
    }

    *a = 0; // Initialize A to 0
    printf("Writer A: initialized shared memory A = %d\n", *a);

    shmdt(a);

    return 0;
}
