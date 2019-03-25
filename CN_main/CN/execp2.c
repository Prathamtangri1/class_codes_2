#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char buff[80];
    read(0, buff, 80);

    printf("%s\n", buff);
    return 0;
}