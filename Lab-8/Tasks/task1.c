#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>

#define NUM_PEOPLE 3

int icecreamRemaining;
sem_t salesman;

void *partA_eatIcecream(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        sem_wait(&salesman); // acquire lock

        if (icecreamRemaining > 0)
        {
            printf("[Part A] Person %d gets ice-cream. Remaining = %d\n",
                   id, icecreamRemaining);
            icecreamRemaining--;
            sem_post(&salesman);
            sleep(1); // eating time
        }
        else
        {
            sem_post(&salesman);
            break;
        }
    }

    printf("[Part A] Person %d finished.\n", id);
    return NULL;
}

void runPartA()
{
    printf("      Running PART (A)\n");

    pthread_t tid[NUM_PEOPLE];
    int ids[NUM_PEOPLE];

    icecreamRemaining = 10;
    sem_init(&salesman, 0, 1);

    for (int i = 0; i < NUM_PEOPLE; i++)
    {
        ids[i] = i + 1;
        pthread_create(&tid[i], NULL, partA_eatIcecream, &ids[i]);
    }

    for (int i = 0; i < NUM_PEOPLE; i++)
        pthread_join(tid[i], NULL);

    sem_destroy(&salesman);
    printf("\n[Part A] All ice-creams finished.\n\n");
}

void *partB_eatIcecream(void *arg)
{
    int id = *(int *)arg;

    while (1)
    {
        // Critical section: only one person gets ice cream
        sem_wait(&salesman);

        if (icecreamRemaining > 0)
        {
            printf("[Part B] Person %d gets ice-cream. Remaining = %d\n",
                   id, icecreamRemaining);
            icecreamRemaining--;
            sem_post(&salesman); // release salesman
        }
        else
        {
            sem_post(&salesman);
            break;
        }

        // Money counting outside critical section
        int delay = (rand() % 2) + 1; // 1–2 seconds
        printf("[Part B] Person %d counting money for %d seconds...\n",
               id, delay);
        sleep(delay);
    }

    printf("[Part B] Person %d finished.\n", id);
    return NULL;
}

void runPartB()
{
    printf("      Running PART (B)\n");

    pthread_t tid[NUM_PEOPLE];
    int ids[NUM_PEOPLE];

    icecreamRemaining = 10;
    sem_init(&salesman, 0, 1);

    srand(time(NULL));

    for (int i = 0; i < NUM_PEOPLE; i++)
    {
        ids[i] = i + 1;
        pthread_create(&tid[i], NULL, partB_eatIcecream, &ids[i]);
    }

    for (int i = 0; i < NUM_PEOPLE; i++)
        pthread_join(tid[i], NULL);

    sem_destroy(&salesman);
    printf("\n[Part B] All ice-creams finished.\n");
}

// =====================================================
//                        MAIN
// =====================================================

int main()
{
    runPartA();
    sleep(2);
    runPartB();
    return 0;
}
