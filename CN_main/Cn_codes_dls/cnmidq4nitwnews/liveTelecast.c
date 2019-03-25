#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

#define MAX_CLIENTS 5
int PORT =5060;
int main()
{

	printf("enter port\n");
	scanf("%d",&PORT);

	struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");

    address.sin_port = htons(PORT);
	int addrlen = sizeof(address);
	char buffer[1024];

	int sfd  = socket(AF_INET,SOCK_STREAM,0);

	if(sfd<0)
	{
		printf("error in socket creation\n");
	}

	printf("socket created\n");


	if( bind(sfd,(struct sockaddr *)&address,addrlen)< 0)
	{
		printf("Bind failed\n");
		return 0;
	}
	
	printf("binded\n");

	if(listen(sfd,MAX_CLIENTS)<0)
	{
		printf("listen failure\n");
		return 0;
	}
	
	printf("listened sfd : %d\n",sfd);
//	int nsfd = accept(sfd , (struct sockaddr *)&address,(socklen_t *)& addrlen);

	int nsfd;
	char *s;s=malloc(1024);
rex :

	nsfd = accept(sfd ,NULL,NULL);

	printf("after acc sys call\n");

	if(nsfd < 0)
	{
		printf("Accept failure\n");
		return 0;
	}

	printf("accepted nsfd : %d\n",nsfd);

	int c = fork();

	if(c==0) //child
	{

	int maxfd;
	if(nsfd<fileno(stdin))
		maxfd = fileno(stdin);
	else
		maxfd = nsfd;

	fd_set readfds;
	FD_ZERO(&readfds);

	while(1)
	{
	close(sfd);
	FD_SET(fileno(stdin),&readfds);
	
	int sx=select(1 , &readfds , NULL,NULL,NULL);
	
	 if(FD_ISSET(fileno(stdin),&readfds))
	 {
	 	malloc(100);
	 scanf("%s",s);
	 send(nsfd,s,strlen(s),0);
	 if(s[0]=='-')
	 	break;
	 }
  	}
    }
   else if(c>0) //parent 
   {
   	close(nsfd);
   	goto rex ;

   }




}