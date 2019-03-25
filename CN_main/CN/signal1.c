#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

void func2(int signum){
    if(signum == SIGUSR2){
        write(1, "Received sig from child\n", sizeof "Received sig from child\n" - 1);
//        printf("Recieved sig from child\n");
    }
}

int main(){
    signal(SIGUSR2, func2);

    pid_t c = fork();
    if(c > 0){
//        kill(c, SIGUSR1);
        printf("parent\n");
        sleep(5);
    }
    else if(c == -1){
        printf("no child");
    }
    else{
//        int parent_id = getppid();
        kill(getppid(), SIGUSR2);
        printf("child\n");
    }
    
}