#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char argv[]){
    int fd, fd_pub;
    int name = argv[1], dir = argv[2];
	
    printf("hello1");

	char* fifo_pub = "./fifo_public";
	mkfifo(fifo_pub, 0666);
		
    printf("hello2");

    fd_pub = open(fifo_pub, O_WRONLY);
    char arr_write[10];
    sprintf(arr_write, "%d%d", name, dir);

    printf("hello3");

    write(fd_pub, arr_write, strlen(arr_write)+1);

    char* myfifo;
    sprintf(myfifo, "./fifo_pri_%c", name);
	mkfifo(myfifo, 0666);
    fd = open(myfifo, O_RDONLY);

    char arr_in[80];

    int cnt = 0;
    while(cnt < 20){
        read(fd, arr_in, sizeof(arr_in));
        printf("Client %d recieves: %s", name, arr_in);
        cnt++;
    }

    close(fd);
    close(fd_pub);

    return 0;
}
