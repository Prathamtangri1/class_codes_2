#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char buff[80];
//    read(0, buff, 80);
    scanf("%79[^\r\n]", buff);
    printf("%s\n", buff);

    FILE *fd = popen("./p3.out", "w");
    
    char string[] = "Pipe from p2 to p3";
    
    fputs(string, fd);

    return 0;
}