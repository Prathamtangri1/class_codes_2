#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void func1(int signum)
{
    /* write is asyc-signal-safe */
    write(1, "Received sig from child\n", sizeof "Received sig from child\n" - 1);
}

int main()
{
    signal(SIGUSR2, func1);

    /* fork returns a pid_t */
    pid_t c = fork();
    if(c > 0) {
        printf("parent\n");
        /* Wait for the child to exit; otherwise, you may not receive the signal */
        if (wait(NULL) == -1) {
            printf("wait(2) failed\n");
            exit(1);
        }
    } else if (c == -1) {
        printf("fork(2) error\n");
        exit(1);
    } else {
        if (kill(getppid(), SIGUSR2) == -1) {
            /* In case kill fails to send signal... */
            printf("kill(2) failed\n");
            exit(1);
        }
        printf("child\n");
    }
}