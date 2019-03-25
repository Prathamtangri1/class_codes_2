#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char *s;s=malloc(1024);
	
	char *fifoname;fifoname=malloc(1024);
	strcpy(fifoname,"rep2");
	mkfifo(fifoname,0666);
	int fd=open(fifoname,O_RDWR);
	//dup2(fd,1);

	while(1)
	{
		scanf("%s",s);
	//	printf("%s",s);
		write(fd,s,strlen(s));
	}
}