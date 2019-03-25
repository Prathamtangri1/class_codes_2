#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    FILE* fd[2];
    fd[0] = popen("./p2.out", "r");
    fd[1] = popen("./p3.out", "r");

    char string1[] = "Pipe from p1 to p2";
    char string2[] = "Pipe from p1 to p3";

    char buff[80];
    
    printf("check1\n");
    fgets(buff, 79, fd[0]);
    printf("P2: %s\n", buff);

    fgets(buff, 79, fd[1]);
    printf("P3: %s\n", buff);

    return 0;
}