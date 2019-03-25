#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdio.h>
#include<errno.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>

#define PORT 7200

int main()
{
	
	struct sockaddr_in servaddr;
	int sfd;
	char *hello = "Hello from client";
	char buffer[1024];

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

rex :
	if((sfd = socket(AF_INET,SOCK_STREAM,0))<0)
	{

		printf("error in creation of socket\n");
		return 0;
	}

	printf("socket created \n");

	if((connect(sfd, (struct sockaddr *)&servaddr,sizeof(servaddr))) <0)
	{
		printf("connection failed\n");
		printf("errno %d \n",errno);

		return 0;
	}
	printf("connected\n");

	int maxfd;
	if(sfd<fileno(stdin))
		maxfd = fileno(stdin);
	else
		maxfd = sfd;

	fd_set readfds;
	FD_ZERO(&readfds);

while(1)
{
	FD_ZERO(&readfds);

	FD_SET(fileno(stdin),&readfds);
	FD_SET(sfd,&readfds);

	int sx=select(maxfd+10, &readfds , NULL,NULL,NULL);

	char *s;s=malloc(100);

	if(FD_ISSET(sfd,&readfds))
	{
	FD_CLR(sfd,&readfds);
	int y=recv(sfd,buffer,1024,0);
	//printf("strlen %d\n",y);
	strncpy(s,buffer,y);
	printf("received : %s\n",s);

	}
	if(FD_ISSET(fileno(stdin),&readfds))
	{
	FD_CLR(fileno(stdin),&readfds);
	scanf("%s",s);
	send(sfd,s,strlen(s),0);
	printf("sent %s\n",s);
	}
}

}