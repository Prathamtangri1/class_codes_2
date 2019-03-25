#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>

int sfd = 0;

int main(){
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;

    if(sfd = socket(AF_INET, SOCK_STREAM, 0) == -1){
        perror("Error in creating socket");
        exit(0);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = 11;
    server
}