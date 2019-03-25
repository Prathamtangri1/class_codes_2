#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 7000

int main()
{
	
	struct sockaddr_in servaddr;
	int sfd;
	char *hello = "Hello from client";
	char buffer[1024];

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	label1 :
	if((sfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{

		printf("error in creation of socket\n");
		return 0;
	}

	printf("socket created \n");

	struct stat statbuf;
	fstat(sfd,&statbuf);
	int x=S_ISSOCK(statbuf.st_mode);
	if(x==0)
		{printf("not a socket\n");
		close(sfd);
		goto label1;
		}
	else 
		printf("is a socket\n");




	if(connect(sfd, (struct sockaddr *)&servaddr,sizeof(servaddr))<0)
	{
		printf("connection failed\n");
		printf("errno %d \n",errno);

	}

	char *s;s=malloc(100);

	scanf("%s",s);
	send(sfd,s,strlen(s),0);
	printf("sent %s\n",s);
	int y=recv(sfd,buffer,1024,0);
	//printf("strlen %d\n",y);
	
	s=malloc(100);
	strncpy(s,buffer,y);
	printf("received : %s\n",s);


}