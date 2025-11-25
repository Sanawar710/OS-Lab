#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUM_THREADS 4

void *printTable(void *arg)
{
    long num = (long)arg;
    printf("\n=== Table of %ld ===\n", num);

    for (int i = 1; i <= 1000; i++)
    {
        printf("%ld x %d = %ld\n", num, i, num * i);
    }

    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    long numbers[NUM_THREADS] = {5, 6, 7, 8};
    int rc;

    for (int i = 0; i < NUM_THREADS; i++)
    {
        printf("Creating thread for table of %ld\n", numbers[i]);
        rc = pthread_create(&threads[i], NULL, printTable, (void *)numbers[i]);

        if (rc)
        {
            printf("Error: Unable to create thread %d, return code %d\n", i, rc);
            exit(-1);
        }
    }

    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll tables printed successfully!\n");
    return 0;
}
