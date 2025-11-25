#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CUSTOMERS 3

// Semaphores for each station
sem_t weigh_sem;
sem_t security_sem;
sem_t boarding_sem;

void *customer_process(void *arg)
{
    int id = *(int *)arg;

    // 1. Weigh Luggage
    sem_wait(&weigh_sem);
    printf("Customer %d is weighing luggage...\n", id);
    sleep(4); // weighing luggage takes 4 sec
    printf("Customer %d finished weighing luggage.\n", id);
    sem_post(&weigh_sem);

    // 2. Security Check
    sem_wait(&security_sem);
    printf("Customer %d is undergoing security check...\n", id);
    sleep(7); // security check takes 7 sec
    printf("Customer %d passed security check.\n", id);
    sem_post(&security_sem);

    // 3. Boarding Pass
    sem_wait(&boarding_sem);
    printf("Customer %d is getting boarding pass...\n", id);
    sleep(3); // boarding pass takes 3 sec
    printf("Customer %d received boarding pass.\n", id);
    sem_post(&boarding_sem);

    return NULL;
}

int main()
{
    pthread_t customers[NUM_CUSTOMERS];
    int ids[NUM_CUSTOMERS];

    // Initialize semaphores to 1 (one passenger at a time)
    sem_init(&weigh_sem, 0, 1);
    sem_init(&security_sem, 0, 1);
    sem_init(&boarding_sem, 0, 1);

    // Create threads
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        ids[i] = i + 1;
        pthread_create(&customers[i], NULL, customer_process, &ids[i]);
    }

    // Wait for all customers
    for (int i = 0; i < NUM_CUSTOMERS; i++)
    {
        pthread_join(customers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&weigh_sem);
    sem_destroy(&security_sem);
    sem_destroy(&boarding_sem);

    return 0;
}
