#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(){
    fd_set rfds;

    struct timeval tv;

    char fifo1[] = "fifo1";
    char fifo2[] = "fifo2";
    char fifo3[] = "fifo3";

    mkfifo(fifo1, 0666);
    mkfifo(fifo2, 0666);
    mkfifo(fifo3, 0666);

    int fd1 = open(fifo1, O_RDONLY);
    int fd2 = open(fifo2, O_RDONLY);
    int fd3 = open(fifo3, O_RDONLY);

    char str1[100], str2[100];

    int maxfd = fd1 > fd2 ? fd1 : fd2 ;
    maxfd = fd3 > maxfd ? fd3 : maxfd ;

    while(1) {
        int retval = -1;
        tv.tv_sec = 3;
        tv.tv_usec = 0; 
        
        do {
//            printf("going in");
            FD_ZERO(&rfds);
            FD_SET(fd1, &rfds);
            FD_SET(fd2, &rfds);
            FD_SET(fd3, &rfds);

            retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
        } while(retval == -1);

        if(retval > 0){
            if(FD_ISSET(fd1, &rfds)) {
                read(fd1, str1, 100);
                printf("Client1: %s\n", str1);
            }
            if(FD_ISSET(fd2, &rfds)) {
                read(fd2, str1, 100);
                printf("Client2: %s\n", str1);
            }
            if(FD_ISSET(fd3, &rfds)) {
                read(fd3, str1, 100);
                printf("Client3: %s\n", str1);
            }
        }
        else if (retval == 0){
//            printf("Nothing to read\n");
        }
        else if (retval == -1){
            perror("Select error");
            break;
        }
    }

    return 0;
}