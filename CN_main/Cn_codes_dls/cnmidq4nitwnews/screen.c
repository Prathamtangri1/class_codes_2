#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/msg.h>
#include<string.h>
#include<poll.h>
#include<pthread.h>
#include <sys/select.h>


int main()
{
	char *fname1,*fname2, *fname3;
	char *s;
	s=malloc(1024);
	fname1=malloc(1024);
	fname2=malloc(1024);
	fname3=malloc(1024);

	strcpy(fname1,"N1");
	strcpy(fname2,"N2");
	strcpy(fname3,"N3")
	mkfifo(fname1,0666);
	mkfifo(fname2,0666);
	mkfifo(fname3,0666);

	int fd[2];

	fd[0]=open(fname1,O_RDWR);
	fd[1]=open(fname2,O_RDWR);
	fd[2]=open(fname2,O_RDWR);

	int maxfd=fd[0];
	if(fd[1]>maxfd)
	maxfd=fd[1];

	fd_set readfds;

	while(1)
	{
	//	printf("while\n");
		FD_ZERO(&readfds);
		FD_SET(fd[0],&readfds);
		FD_SET(fd[1],&readfds);

		select(maxfd+1,&readfds,NULL,NULL,NULL);

		for(int i=0;i<2;i++)
		{
			if(FD_ISSET(fd[i],&readfds))
			{
				int y=read(fd[i],s,1024);
				if(strlen(s)>0 && y>0)
				printf("from %d : %s\n",i,s);
			}
		}
	}

	
}
