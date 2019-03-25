#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int c = 0, i = 4;
    printf("Hello1");

    c = fork();

    if(c > 0){
        printf("Hello2");
        i++;
        printf("Hello3");
    }
    else{
        printf("Hello4");
    }
}