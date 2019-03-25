#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() { 
    int pp[2];
    pipe(pp);
    char buff[80];
/*     write(pp[1], "checking", 9);

    read(pp[0], buff, 80);
    printf("%s\n", buff);
 */
    char string[] = "Hello, world!\n";

    pid_t cpid = fork();

    if(cpid == -1){
        perror("fork");
        exit(1);
    } 
    else if(cpid == 0) {
        close(pp[0]);
        write(pp[1], string, (strlen(string)+1));
        exit(0);
    }
    else {
        close(pp[1]);
        int nbytes = read(pp[0], buff, sizeof(buff));
        printf("Received string: %s", buff);
    }
}