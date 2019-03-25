#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    FILE* fd[2];
    fd[0] = popen("./p2.out", "w");
    fd[1] = popen("./p3.out", "w");

    char string1[] = "Pipe from p1 to p2";
    char string2[] = "Pipe from p1 to p3";

    fputs(string1, fd[0]);
    fputs(string2, fd[1]);

    return 0;
}