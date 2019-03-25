#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
//    char string[] = "Pipe from p2 to p1";
    char string[80];
    
    scanf("%79[^\r\n]", string);
    printf("%s", string);
//    for(int i = 5; i < 1000 ; i++);
//    sleep(5);

    return 0;
}