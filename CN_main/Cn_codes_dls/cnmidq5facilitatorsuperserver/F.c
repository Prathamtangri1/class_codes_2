#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<errno.h>
#include<sys/select.h>
#include<signal.h>
#include<pthread.h>

#define PORT 8088
#define limit 25
#define MAXN  25

	int fds[MAXN];
	char *path[MAXN];
	int processID[MAXN];

	int count=1;

int sfd;
struct sockaddr_in cliaddr[5*MAXN];
int count1=0;

void *fsr(void *p);

int info()
{
	//send last address to all clients

			char *buffer;
			buffer=malloc(100);
			strcpy(buffer,path[count-2]);

			for(int i=0;i<count1;i++) //send everything to client
			{
			socklen_t d = (socklen_t) sizeof(cliaddr[i]);
			int w = sendto(sfd,(const char *)buffer,strlen(buffer),MSG_CONFIRM,(const struct sockaddr *)&cliaddr[i],d);
			}
}

int getPort(char *s)
{
	int x=0;
	int i;
	for(i=0;s[i]!='\0' && s[i]>='0' && s[i]<='9' ; i++)
	{
		x=x*10+s[i]-'0';
	}
	return x;
}

int main()
{

	signal(SIGUSR1,info);

	struct sockaddr_in servaddr;

	
	if((sfd = socket(AF_INET,SOCK_DGRAM,0))<0)
	{
	printf("socket failed\n");
	}
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	if(bind(sfd,(const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0)
	{
	printf("failed to bind\n");
	return 0;
	}


	printf("binded sfd : %d\n",sfd);

	

	pthread_t tid;
	pthread_create(&tid,NULL,fsr,NULL);


	char buffer[1024];

	char *s;
	fds[0]=0;
	fd_set readfds;
	FD_SET(fds[0],&readfds);
	int maxfd=0;
rex :
	while(1)
	{
		printf("WHILE count : %d\n",count);

		for(int i=0;i<count;i++)
		{
			FD_SET(fds[i],&readfds);
		}

		printf("B4 select\n");
		select(maxfd+1,&readfds,NULL,NULL,NULL);
		printf("After select\n");

		for(int i=1;i<count;i++)
		{
			if(FD_ISSET(fds[i],&readfds))
			{
			printf("send signal to process\n");
			kill(processID[i-1],SIGUSR1);
			}
		}

		if(FD_ISSET(fds[0],&readfds)) //stdin
		{
			s=malloc(100);
			int y=read(fds[0],s,1024);
			
			int p=getPort(s);
			char *s1;s1=malloc(100);
			sprintf(s1,"%d",p);
			int x=strlen(s1);
			s=s+x+1;

			printf("port %d\n",p);
			
			path[count-1]=malloc(100);
			strcpy(path[count-1],s);

			struct sockaddr_in address;
   			address.sin_family = AF_INET;
    		address.sin_addr.s_addr = inet_addr("127.0.0.1");
		    address.sin_port = htons(p);
			int addrlen = sizeof(address);
	
			fds[count]  = socket(AF_INET,SOCK_STREAM,0);
			
			int temp=1;
/*
		if(setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR||SO_REUSEPORT,&temp,sizeof(int)) <0)
		{
		printf("set sock error");
		printf("errno %d\n",errno);
		return 0;
		}
*/			if(maxfd<fds[count])
			maxfd=fds[count];
			bind(fds[count],(struct sockaddr *)&address,addrlen);
			listen(fds[count],MAXN);
			count++;
			printf("b4 fork\n");

			int c=fork();
			if(c>0)
				processID[count-2]=c;
				//goto rex;}
			else
				{   char *news;news=malloc(100);
					strncpy(news,s,strlen(s)-1);
					s=malloc(100);
					sprintf(s,"%d",fds[count-1]);
					int x=execlp(news,s,NULL);
					break;
			
				}

			printf("After if-else c:%d\n",c);
				kill(getpid(),SIGUSR1);
		}
	}

	//memset(&cliaddr,0,sizeof(cliaddr));
/*
	int len,n;
	printf("before rev");
	 n = recvfrom(sfd,(char *)buffer,1024,0,(struct sockaddr *)&cliaddr,&len);
*/
/*
	 char ad[20];

	inet_ntop(AF_INET,&(cliaddr.sin_addr),ad,20);
	int x = ntohs(cliaddr.sin_port);
    
	printf("ports : %d\n",x);
	printf("ip add :%s\n",ad);
*/
/*	 buffer[n]='\0';

	 printf("Cilent sent : %s\n",buffer);
	 strcpy(buffer,"Hi im server");

	 socklen_t d = (socklen_t) sizeof(cliaddr);

	int w = sendto(sfd,(const char *)buffer,strlen(buffer),MSG_CONFIRM,(const struct sockaddr *)&cliaddr,d);

	 printf("message sent w : %d\n",w);
	 if(w<0)
	 	perror("errno");

	 sleep(2);
*/


}

void *fsr(void *p)
{

	char *buffer;
	printf("Inside thread\n");
	while(1)
	{
			printf("While thread\n");
			buffer=malloc(100);
			struct sockaddr_in caddr;
			int len;
			int n = recvfrom(sfd,(char *)buffer,1024,0,(struct sockaddr *)&caddr,&len); //request from client
			cliaddr[count1]=caddr; //store client
			count1++;
			socklen_t d = (socklen_t) sizeof(caddr);
			
			for(int i=0;i<count-1;i++) //send everything to client
			{
			printf("sending to client %d\n",i);
			buffer=malloc(100);
			strcpy(buffer,path[i]);
			int w = sendto(sfd,(const char *)buffer,strlen(buffer),MSG_CONFIRM,(const struct sockaddr *)&caddr,d);
			}
	}

}