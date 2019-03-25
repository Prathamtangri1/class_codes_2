#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <poll.h>
#include <sys/time.h>


#define MAX_CLIENTS 5
#define num 2

int cfd[num]={0};
int sfd[num];

int sighand1() {
	cfd[0]--;
	printf("inside sighand0 :%d\n",cfd[0]);
	signal(SIGUSR1,sighand1);

}
int sighand2() {
	cfd[1]--;
	printf("inside sighand1 :%d\n",cfd[1]);
	signal(SIGUSR2,sighand2);
}
void *ser2fn(void *p);


int main() {
	signal(SIGUSR1,sighand1);
	signal(SIGUSR2,sighand2);

	struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
   // address.sin_port = htons(PORT);

	char buffer[1024];
	int limit[2]={25,15};
	int PORT[2]={7000,7111};

	for(int i=0;i<num;i++) {
	    printf("port i %d\n",PORT[i]);
		address.sin_port = htons(PORT[i]);
		int addrlen = sizeof(address);

		sfd[i] = socket(AF_INET,SOCK_STREAM,0);
	
		if(sfd[i]<0) {
			printf("error in socket creation\n");
		}
		printf("socket created\n");


		if( bind(sfd[i],(struct sockaddr *)&address,addrlen)< 0) {
			printf("Bind failed\n");
			return 0;
		}
		printf("binded\n");

		if(listen(sfd[i],limit[i])<0) {
			printf("listen failure\n");
			return 0;
		}
		printf("listened sfd : %d\n",sfd[i]);
	}

	int nsfd[num];
	struct pollfd pfd[num];
	
	for(int i=0;i<num;i++) {
		pfd[i].fd=sfd[i];
		pfd[i].events=POLLIN;
	}
			
		

	label1 :;
		struct timeval tv;
	
		while(1) {
			printf("while\n");
			
			poll(pfd,num,3000);
			
			printf("after select\n");

			//sleep(2);

			for(int i=0;i<num;i++)
			{
				//printf("inside for loop i:%d\n",i);
				if(i==0 && pfd[i].revents==POLLIN && cfd[i]<limit[i])
				{	
					//FD_CLR(sfd[i],&readsfds);

					printf("inside 0\n");
					cfd[0]++;				
					//FD_CLR(sfd[i],&readsfds);
					//printf("i :%d\n",i);

					nsfd[i] = accept(sfd[i],NULL,NULL);
					int c = fork();
					if(c>0) //parent
					{
						///printf("parent\n");
						close(nsfd[i]);
						goto label1;
					}
					else if(c==0) //child
					{

						close(sfd[i]);
						int x=dup(0); //save stdin and stdout
						int y=dup(1);
						char *r0,*r1,*s;r0=malloc(100);s=malloc(100);r1=malloc(100);
						strcpy(s,"./s1");
						sprintf(r0,"%d",x);
						sprintf(r1,"%d",y);
						//printf("child\n");

						
						dup2(nsfd[i],0);
						dup2(nsfd[i],1);

						execlp(s,r0,r1,NULL); 
					}

				}
				if(pfd[i].revents==POLLIN && i==1 && cfd[i]<limit[i])
				{	
					//	FD_CLR(sfd[i],&readsfds);

							printf("inside 1\n");
							cfd[1]++;
							nsfd[i] = accept(sfd[i],NULL,NULL);
							int a[1]={nsfd[i]};
							pthread_t sid;
							pthread_create(&sid,NULL,ser2fn,(void *)a);
							//pthread_join(sid,NULL);
							printf("okayy\n");

				}
				printf("Hello\n");
			}
		}

	return 0;
}

void *ser2fn(void *p){
	printf("inside ser fn\n");
	int *a=(int *)p;
	int nsfd=*a;
	printf("nsfd :%d\n",nsfd);
	char buffer[1024];
	char *s;s=malloc(1024);
	int y=recv(nsfd,buffer,1024,0);
    sprintf(s,"%d",y);///length
    printf("sending s:%s\n",s);
    send(nsfd,s,strlen(s),0);
	
	//signal after completion
	kill(getpid(),SIGUSR2);
}
