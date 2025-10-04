#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    
    printf("I am Process 1 and my PID is %d\n", getpid());
    
    // Create process 2
    pid = fork();
    if (pid == 0) {
        printf("I am Process 2 and my PID is %d\n", getpid());
        
        // Create process 4
        pid = fork();
        if (pid == 0) {
            printf("I am Process 4 and my PID is %d\n", getpid());
            
            // Create process 8
            pid = fork();
            if (pid == 0) {
                printf("I am Process 8 and my PID is %d\n", getpid());
                exit(0);
            }
            
            // Create process 9
            pid = fork();
            if (pid == 0) {
                printf("I am Process 9 and my PID is %d\n", getpid());
                exit(0);
            }
            
            wait(NULL);
            wait(NULL);
            exit(0);
        }
        
        // Create process 5
        pid = fork();
        if (pid == 0) {
            printf("I am Process 5 and my PID is %d\n", getpid());
            exit(0);
        }
        
        wait(NULL);
        wait(NULL);
        exit(0);
    }
    
    // Create process 3
    pid = fork();
    if (pid == 0) {
        printf("I am Process 3 and my PID is %d\n", getpid());
        
        // Create process 6
        pid = fork();
        if (pid == 0) {
            printf("I am Process 6 and my PID is %d\n", getpid());
            exit(0);
        }
        
        // Create process 7
        pid = fork();
        if (pid == 0) {
            printf("I am Process 7 and my PID is %d\n", getpid());
            exit(0);
        }
        
        wait(NULL);
        wait(NULL);
        exit(0);
    }
    
    // Parent waits for all children
    wait(NULL);
    wait(NULL);
    
    return 0;
}
