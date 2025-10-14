// Task-4_C.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY_A 1234
#define SHM_KEY_B 5678

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <n_iterations>\n", argv[0]);
        exit(1);
    }

    int n = atoi(argv[1]);
    if (n < 1 || n > 100)
    {
        printf("Please enter n between 1 and 100.\n");
        exit(1);
    }

    int shmidA = shmget(SHM_KEY_A, sizeof(int), 0666);
    int shmidB = shmget(SHM_KEY_B, sizeof(int), 0666);
    if (shmidA < 0 || shmidB < 0)
    {
        perror("shmget");
        exit(1);
    }

    int *a = (int *)shmat(shmidA, NULL, 0);
    int *b = (int *)shmat(shmidB, NULL, 0);
    if (a == (void *)-1 || b == (void *)-1)
    {
        perror("shmat");
        exit(1);
    }

    printf("Fibonacci series: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", *a);

        int sum = *a + *b;
        *a = *b;
        *b = sum;
    }
    printf("\n");

    shmdt(a);
    shmdt(b);

    return 0;
}
