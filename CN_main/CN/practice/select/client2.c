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
    char fifo[] = "fifo2";
    mkfifo(fifo, 0666);

    int fd = open(fifo, O_WRONLY);
    
    char buffer[100];

    while(1){
        gets(buffer);
        write(fd, buffer, strlen(buffer)+1);
    }
}