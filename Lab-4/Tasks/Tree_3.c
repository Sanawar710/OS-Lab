#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    printf("I am Process 8 and my PID is %d\n", getpid());

    pid_t pid0 = fork();   // create Node 0
   
    if (pid0 == 0) 
    {
        // Inside Process 0
        printf("I am Process 0 and my PID is %d\n", getpid());

        pid_t pid7 = fork();   // create Node 7
        if (pid7 == 0)
        {
            printf("I am Process 7 and my PID is %d\n", getpid());
        } 
        
        else
         {
            pid_t pid2 = fork();   // create Node 2
            if (pid2 == 0) 
            {
                printf("I am Process 2 and my PID is %d\n", getpid());
            }
           
            else 
            {
                // Process 0 waits for both children
                wait(NULL);
                wait(NULL);
            }
        }

    } 
    return 0;
}
