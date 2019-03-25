#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>



void *sendfn(void *p);
void *recvfn(void *p);

int nsfd;

int main(int argc,char *argv[])
{


	//printf("inside s1 argc = %d\n",argc);

    nsfd = dup(0);
    dup2(atoi(argv[0]),0);
    dup2(atoi(argv[1]),1);

//	printf("%d",nsfd);
//	nsfd = dup(2);


	char *s;s=malloc(100);
 	char buffer[1024];
//receive data from client , print on screen , receive data from stdin , send it to client   

    int y=recv(nsfd,buffer,1024,0);
    strncpy(s,buffer,y);
	printf("received in s1: %s\n",s);
	scanf("%s",s);
	send(nsfd,s,strlen(s),0);
	
	//signal after completion
	kill(getppid(),SIGUSR1);
}
