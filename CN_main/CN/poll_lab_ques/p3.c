#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <time.h>

int main() {
    /* while(1){
        char string[80];
        
        scanf("%79[^\r\n]", string);
        printf("%s", string);
    }
    return 0; */
    srand(time(NULL));
    char buff[] = "p3 is aw";
    int i = 0;
    while(i < 10){
//        printf("p3");
        write(1, buff, 11);
        sleep(rand() % 5);
        i++;
    }
    return 0;
}