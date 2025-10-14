#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int pipe1[2]; // For parent -> child communication
    int pipe2[2]; // For child -> parent communication

    // Create the first pipe (unidirectional)
    if (pipe(pipe1) == -1)
    {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }
    printf("Unidirectional pipe created: pipe1[1] for writing, pipe1[0] for reading\n");

    // Now create second pipe to simulate bidirectional communication
    if (pipe(pipe2) == -1)
    {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }
    printf("Second pipe created to allow bidirectional communication\n");

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid > 0)
    {
        // Parent process
        close(pipe1[0]); // Close read end of pipe1 (parent writes)
        close(pipe2[1]); // Close write end of pipe2 (parent reads)

        char *msg = "Hello from parent!";
        write(pipe1[1], msg, strlen(msg));
        close(pipe1[1]); // Finished writing

        char buffer[100];
        ssize_t n = read(pipe2[0], buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n] = '\0';
            printf("Parent received: %s\n", buffer);
        }
        close(pipe2[0]);

        wait(NULL); // Wait for child to finish
    }
    else
    {
        // Child process
        close(pipe1[1]); // Close write end of pipe1 (child reads)
        close(pipe2[0]); // Close read end of pipe2 (child writes)

        char buffer[100];
        ssize_t n = read(pipe1[0], buffer, sizeof(buffer) - 1);
        if (n > 0)
        {
            buffer[n] = '\0';
            printf("Child received: %s\n", buffer);
        }
        close(pipe1[0]);

        char *reply = "Hello from child!";
        write(pipe2[1], reply, strlen(reply));
        close(pipe2[1]);

        exit(EXIT_SUCCESS);
    }

    return 0;
}
