#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() { 
    int p2c[2], c2p[2];
    pipe(p2c);
    pipe(c2p);

    char buff[80];
/* 
    write(p2c[1], "checking", 9);
    read(p2c[0], buff, 80);
    printf("%s\n", buff);

 */    
    char string[] = "Hello, world!\n";

    pid_t cpid = fork();

    if(cpid == -1) {
        perror("fork");
        exit(1);
    } 
    else if(cpid == 0) {
        close(c2p[0]);
        write(c2p[1], string, (strlen(string)+1));

        close(p2c[1]);
        int nbytes = read(p2c[0], buff, sizeof(buff));
        printf("Received string: %s", buff);

        exit(0);
    }
    else {
        close(c2p[1]);
        int nbytes = read(c2p[0], buff, sizeof(buff));
        printf("Received string: %s", buff);

        close(p2c[0]);
        write(p2c[1], string, (strlen(string)+1));
    }
}