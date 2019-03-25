#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    char buff[80];
    scanf("%79[^\r\n]", buff);

    printf("%s\n", buff);
    return 0;
}