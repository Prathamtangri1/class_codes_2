#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <poll.h>

int main() {
    char buff[80];

    FILE* fd[5];

    fd[0] = popen("./p2.out", "r");
    fd[1] = popen("./p3.out", "r");
    fd[2] = popen("./p4.out", "r");
    fd[3] = popen("./p5.out", "r");
//    fd[4] = popen("./p6.out", "w");

    struct pollfd pfds[4];
    int timeout;

    for(int i = 0 ; i < 4 ; i++){
        pfds[i].fd = fd[i];
        pfds[i].events = 0;
        pfds[i].events |= POLLIN;
    }

    timeout = 5000;

    while(1) {
        int pret = poll(pfds, 4, timeout);

        if(pret == 0) {
            printf("No input from P2-P5\n");
        }
        else {
            printf("comes in once\n");
            for(int i = 0 ; i < 4 ; i++){
                if(pfds[i].revents & POLLOUT){
                    fgets(buff, 79, fd[0]);
                    printf("P%d: %s\n", i, buff);
                }
            }
            
/*             scanf("%79[^\r\n]", buff);
            printf("%s\n", buff); */
        }

        printf("one rev\n");
    }
    return 0;
}