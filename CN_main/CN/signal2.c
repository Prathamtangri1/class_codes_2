#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void func1(int signum){
    if(signum == SIGUSR2){
        printf("Received sig from child\n");
    }
}

int main(){
    signal(SIGUSR2, func1);

    int c = fork();
    if(c > 0){
        printf("parent\n");
    }
    else if(c == -1){
        printf("No child");
    }
    else{
        kill(getppid(), SIGUSR2);
        printf("child\n");
    }

}