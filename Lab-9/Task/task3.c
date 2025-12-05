#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <semaphore.h>

#define NUM_THREADS 4

sem_t sem;               // Semaphore for critical section
volatile sig_atomic_t time_up = 0;   // Flag set by signal handler

// Signal handler for alarm
void alarm_handler(int signo) {
    time_up = 1;    // Notify thread that 5 seconds have passed
}

void *printTable(void *arg) {
    long num = (long)arg;

    // Enter critical section
    sem_wait(&sem);

    printf("\n[Thread %ld] Entered critical section\n", num);

    // Reset flag before setting alarm
    time_up = 0;
    signal(SIGALRM, alarm_handler);
    alarm(5);   // Stay in CS for 5 seconds

    int i = 1;
    while (!time_up && i <= 1000) {
        printf("%ld x %d = %ld\n", num, i, num * i);
        i++;
        usleep(1000);   // Small delay so 1000 lines don't finish instantly
    }

    printf("[Thread %ld] Exiting critical section after 5 seconds\n", num);

    // Exit critical section
    sem_post(&sem);

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    long numbers[NUM_THREADS] = {5, 6, 7, 8};

    // Initialize semaphore
    sem_init(&sem, 0, 1);

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        printf("Creating thread for table of %ld\n", numbers[i]);
        if (pthread_create(&threads[i], NULL, printTable, (void *)numbers[i])) {
            printf("Error creating thread %d\n", i);
            exit(1);
        }
    }

    // Wait for all threads
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nAll threads finished!\n");

    sem_destroy(&sem);
    return 0;
}

