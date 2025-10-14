#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t pid_temp;

    pid_temp = fork();

    if (pid_temp == 0) // Tier 1 child
    {
        printf("B \n");

        pid_t pid_t2;
        pid_t2 = fork();

        if (pid_t2 == 0)
        {
            printf("E.2 \n");
        }

        else if (pid_t2 > 0)
        {
            printf("F.2 \n");
        }
    }

    else if (pid_temp > 0) // Initial parent
    {
        printf("A \n");

        pid_t pid_t3;
        pid_t3 = fork();

        if (pid_t3 == 0)
        {
            printf("D.1 \n");
            pid_t pid_t4 = fork();

            if (pid_t4 == 0)
            {
                printf("G.3 \n");
            }

            else if (pid_t4 > 0)
            {
                printf("H.3 \n");
            }
        }
        else if (pid_t3 > 0)
        {
            printf("C.1 \n");
        }
    }
}
