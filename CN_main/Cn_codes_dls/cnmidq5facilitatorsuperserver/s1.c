#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>
#include<errno.h>

#define MAX_CLIENTS 5
#define PORT 7100 

int sfd;
void *recvmessage(void *);


int handle()
{
	int nsfd = accept(sfd ,NULL,NULL);
	printf("accepted\n");
	pthread_t pid;
	int a[1]={nsfd};
	pthread_create(pid,NULL,recvmessage,(void *)a);
	signal(SIGUSR1,handle);

}


int main(int argc,char *argv[])
{

	printf("in s1\n");
	signal(SIGUSR1,handle);

	
	printf("Hey\n");
	sfd=atoi(argv[0]);
	printf("Hey\n");

	while(1)
	{

	}



}

void *recvmessage(void *p){

	int *a=(int *)p;
	int nsfd=*a;
	char *s;
	
	while(1)
	{
	printf("S-inside while loop\n");	
	s=malloc(100);
	int y=recv(nsfd,s,1024,0);
	printf("received : %s\n",s);
	int d=strlen(s);
	s=malloc(100);
	sprintf(s,"%d",d);
	send(nsfd,s,strlen(s),0);
	}

}