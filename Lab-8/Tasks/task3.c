#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

typedef struct
{
    sem_t sem;   // unnamed semaphore
    int balance; // shared account balance
} shared_data;

int main()
{
    // Create shared memory
    shared_data *shm = mmap(NULL, sizeof(shared_data),
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shm == MAP_FAILED)
    {
        perror("mmap");
        exit(1);
    }

    // Initialize shared balance
    shm->balance = 1000; // initial account balance

    // Initialize unnamed semaphore, shared between processes
    if (sem_init(&shm->sem, 1, 1) == -1)
    {
        perror("sem_init");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    // CHILD PROCESS → Process A (Deposit Service)
    if (pid == 0)
    {
        for (int i = 0; i < 5; i++)
        {
            sem_wait(&shm->sem); // lock semaphore

            int deposit_amount = 200;
            shm->balance += deposit_amount;
            printf("[Deposit] +%d → New Balance = %d\n",
                   deposit_amount, shm->balance);

            sem_post(&shm->sem); // release semaphore

            sleep(2); // deposit every 2 seconds
        }
        exit(0);
    }

    // PARENT PROCESS → Process B (Withdrawal Service)
    for (int i = 0; i < 5; i++)
    {
        sem_wait(&shm->sem); // lock semaphore

        int withdrawal_amount = 250;

        if (shm->balance >= withdrawal_amount)
        {
            shm->balance -= withdrawal_amount;
            printf("[Withdraw] -%d → New Balance = %d\n",
                   withdrawal_amount, shm->balance);
        }
        else
        {
            printf("[Withdraw] FAILED — Insufficient funds (Balance = %d)\n",
                   shm->balance);
        }

        sem_post(&shm->sem); // release semaphore

        sleep(3); // withdraw every 3 seconds
    }

    // Wait for deposit process to finish
    wait(NULL);

    // Cleanup semaphore
    sem_destroy(&shm->sem);

    // Unmap shared memory
    munmap(shm, sizeof(shared_data));

    return 0;
}
