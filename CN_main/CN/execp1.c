#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pp[2]; int fd;
    pipe(pp);
    
    char string[] = "Pipe from p1 to p2";
    
    pid_t cpid = fork();

    if(cpid == -1) {
        perror("Fork failed");
        exit(1);
    }
    else if(cpid == 0) {
        close(pp[1]);
        dup2(pp[0], 0);
        char *args[]={"./execp2.out",NULL}; 
        printf("Child gng to exec\n");
        execv(args[0],args); 
    }
    else {
        close(pp[0]);
        write(pp[1], string, (strlen(string) + 1));
        printf("parent has written\n");
        wait(NULL);
    }

    return 0;
}