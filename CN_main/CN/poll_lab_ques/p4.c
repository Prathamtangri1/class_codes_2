#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));
    while(1){
        printf("p4");
        sleep(rand() % 5);
    }
    return 0;
}