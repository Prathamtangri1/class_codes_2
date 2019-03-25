#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <poll.h>

int main(int argc, char* argv[]){
//    int fd = 0;
//    FILE* fd = popen("./p3.out", "r");
    int fd[2];
    pipe(fd);

    pid_t cpid = fork();

    if(cpid == 0){
        close(fd[0]);
        dup2(fd[1], 1);
        char *args[]={"./p2.out",NULL}; 
        printf("Child gng to exec\n");
        execv(args[0],args); 
    }
    else{
        close(fd[1]);
        char buff[11];
        int ret, pret;

        struct pollfd fds[1];
        int timeout;
        int cnt = 0;
        while(cnt < 10){
            fds[0].fd = fd[0];
            fds[0].events = 0;
            fds[0].events |= POLLIN;

            timeout = 5000;

            pret = poll(fds, 1, timeout);

            if(pret == 0){
                printf("ret = %d\n", ret);
                printf("    timeout\n");
            }
            else{
                memset((void *)buff, 0, 11);
                ret = read(fd[0], (void*) buff, 10);
                printf("ret = %d\n", ret);

                if(ret != -1){
                    printf("buff = %s\n", buff);
                }
            }
            cnt++;
        }
    }
}