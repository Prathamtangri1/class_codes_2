#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<poll.h>
#include<pthread.h>

int rfd;
void *takeInp(void *);

int main(int argc,char *argv[])
{
	int count =1;

	char *s,*fname;s=malloc(100);
	rfd=open("docreport.txt",O_CREAT|O_RDWR,S_IRUSR|S_IWUSR);
	printf("rfd %d\n",rfd);

	printf("inside docwriter\n");


	


while(1)
{
	    printf("DocWriterwhile\n");
		s=malloc(100);
		//printf("dw1\n");
		read(0,s,1024);
		printf("received from editor :%s\n",s);
		if(strlen(s)<=0) continue; 
		mkfifo(s,0666);
		//printf("dw2\n");

		int newfd=open(s,O_RDWR);
		int a[2]={newfd};
		pthread_t tid;
		pthread_create(&tid,NULL,takeInp,(void *)a);
	//	printf("okayy");
		//printf("dw3\n");
	
}

}
void *takeInp(void *p)
{
	printf("inside thread\n");
	int *x=(int *)p;
	int fd=*x;
	char *s;
		while(1)
		{
		s=malloc(100);
		int y=read(fd,s,1024); //read from reporter
		strcat(s,"\n");
		printf("writing into the document %s\n",s);
		write(rfd,s,strlen(s));  
		}
}