#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_VOLUNTEERS 4
#define NUM_PARTICIPANTS 100

int participant_count = 0;
pthread_mutex_t count_mutex;

void *volunteer1_registration(void *arg);
void *volunteer2_announcements(void *arg);
void *volunteer3_sponsors(void *arg);
void *volunteer4_queries(void *arg);

void *(*volunteer_tasks[NUM_VOLUNTEERS])(void *) = {
    volunteer1_registration,
    volunteer2_announcements,
    volunteer3_sponsors,
    volunteer4_queries};

int main()
{
    pthread_t volunteers[NUM_VOLUNTEERS];
    int volunteer_ids[NUM_VOLUNTEERS];
    int i;

    if (pthread_mutex_init(&count_mutex, NULL) != 0)
    {
        perror("Mutex initialization failed");
        return 1;
    }

    printf("--- Procom Front Desk System Initialized ---\n");

    for (i = 0; i < NUM_VOLUNTEERS; i++)
    {
        volunteer_ids[i] = i + 1; // ID 1 to 4
        printf("Starting Volunteer %d thread...\n", volunteer_ids[i]);

        if (pthread_create(&volunteers[i], NULL, volunteer_tasks[i], (void *)&volunteer_ids[i]) != 0)
        {
            perror("Thread creation failed");
            return 1;
        }
    }

    for (i = 0; i < NUM_VOLUNTEERS; i++)
    {
        pthread_join(volunteers[i], NULL);
    }

    printf("\n--- All 100 Participants Have Been Served ---\n");
    pthread_mutex_destroy(&count_mutex);
    return 0;
}

void *volunteer1_registration(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        pthread_mutex_lock(&count_mutex);
        if (participant_count < NUM_PARTICIPANTS)
        {
            participant_count++;
            int current_p = participant_count;
            pthread_mutex_unlock(&count_mutex);
            printf("[V%d - Registration]: On-day registration for Participant %d completed.\n", id, current_p);
            usleep(10000);
        }
        else
        {
            pthread_mutex_unlock(&count_mutex);
            break;
        }
    }
    printf("Volunteer %d (Registration) finished their shift.\n", id);
    return NULL;
}

void *volunteer2_announcements(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        pthread_mutex_lock(&count_mutex);
        if (participant_count < NUM_PARTICIPANTS)
        {
            participant_count++;
            int current_p = participant_count;
            pthread_mutex_unlock(&count_mutex);

            // Critical task for Volunteer 2
            printf("[V%d - Announcements]: Welcome announcement made for Participant %d.\n", id, current_p);
            usleep(20000); // Simulate work delay (20ms)
        }
        else
        {
            pthread_mutex_unlock(&count_mutex);
            break;
        }
    }
    printf("Volunteer %d (Announcements) finished their shift.\n", id);
    return NULL;
}

void *volunteer3_sponsors(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        pthread_mutex_lock(&count_mutex);
        if (participant_count < NUM_PARTICIPANTS)
        {
            participant_count++;
            int current_p = participant_count;
            pthread_mutex_unlock(&count_mutex);

            printf("[V%d - Sponsors]: Sponsor info packet given to Participant %d.\n", id, current_p);
            usleep(30000);
        }
        else
        {
            pthread_mutex_unlock(&count_mutex);
            break;
        }
    }
    printf("Volunteer %d (Sponsors) finished their shift.\n", id);
    return NULL;
}

void *volunteer4_queries(void *arg)
{
    int id = *((int *)arg);
    while (1)
    {
        pthread_mutex_lock(&count_mutex);
        if (participant_count < NUM_PARTICIPANTS)
        {
            participant_count++;
            int current_p = participant_count;
            pthread_mutex_unlock(&count_mutex);

            printf("[V%d - Queries]: Basic query resolved for Participant %d.\n", id, current_p);
            usleep(15000); // Simulate work delay (15ms)
        }
        else
        {
            pthread_mutex_unlock(&count_mutex);
            break;
        }
    }
    printf("Volunteer %d (Queries) finished their shift.\n", id);
    return NULL;
}
