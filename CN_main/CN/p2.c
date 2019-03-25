#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int wait(int var){
    while(var == 0);
    
    var--;
    return var;
}

int signal(int var){
    var++;
    return var;
}

int main(){
    int x = 0, y = 0, s1 = 0, s2 = 1, lpcount = 0;

    int c = fork();

    if(c == 0){
        while(lpcount < 10){
            s2 = wait(s2);
            x = y + 1;
            printf("p1 x: %d s2 = %d s1 = %d ", x, s2, s1);
            s1 = signal(s1);
            lpcount++;
        }
    }
    else{
        while(lpcount < 10){
            s1 = wait(s1);
            y = x + 1;
            printf("p2 y: %d s2 = %d s1 = %d ", y, s2, s1);
            s2 = signal(s2);
            lpcount++;
        }
    }

    return 0;
}