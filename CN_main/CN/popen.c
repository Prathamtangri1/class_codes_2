#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    FILE *fd = popen("./execp2.out", "w");
    
    char string[] = "Pipe from p1 to p2";
    
    fputs(string, fd);

    return 0;
}