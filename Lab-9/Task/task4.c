#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>

// Signal handler for SIGPIPE
void sigpipe_handler(int signum) {
printf("\n[WRITER] SIGPIPE signal received!\n");
printf("[WRITER] Attempted to write to a pipe with no reader.\n");
printf("[WRITER] The reader process has already terminated.\n");
printf("[WRITER] Exiting gracefully…\n");
exit(0);
}

int main() {
int pipefd[2];
pid_t pid;


// Create pipe
if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(1);
}

printf("=== SIGPIPE Demonstration ===\n");
printf("Scenario: Writer continues after reader exits\n\n");

// Fork a child process
pid = fork();

if (pid == -1) {
    perror("fork");
    exit(1);
}

if (pid == 0) {
    // READER PROCESS (Child)
    close(pipefd[1]);  // Close write end
    
    printf("[READER] Reader process started (PID: %d)\n", getpid());
    printf("[READER] Reading data from pipe...\n");
    
    char buffer[100];
    int bytes_read = read(pipefd[0], buffer, sizeof(buffer));
    
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("[READER] Received: %s\n", buffer);
    }
    
    printf("[READER] Task completed. Exiting early...\n");
    close(pipefd[0]);
    exit(0);
    
} else {
    // WRITER PROCESS (Parent)
    close(pipefd[0]);  // Close read end
    
    // Register SIGPIPE handler
    signal(SIGPIPE, sigpipe_handler);
    
    printf("[WRITER] Writer process started (PID: %d)\n", getpid());
    printf("[WRITER] Sending first message to reader...\n");
    
    char* msg1 = "First message";
    write(pipefd[1], msg1, strlen(msg1));
    
    printf("[WRITER] First message sent successfully.\n");
    
    // Wait for reader to exit
    sleep(2);
    printf("\n[WRITER] Waiting for reader to finish...\n");
    wait(NULL);
    printf("[WRITER] Reader process has terminated.\n\n");
    
    // Try to write again - this will trigger SIGPIPE
    printf("[WRITER] Attempting to send second message...\n");
    printf("[WRITER] (Reader no longer exists!)\n");
    
    sleep(1);
    
    char* msg2 = "Second message - this should trigger SIGPIPE";
    ssize_t result = write(pipefd[1], msg2, strlen(msg2));
    
    // This line won't be reached if SIGPIPE terminates the process
    if (result == -1) {
        perror("[WRITER] Write failed");
    }
    
    printf("[WRITER] This line should not be printed!\n");
    
    close(pipefd[1]);
}

return 0;


}
