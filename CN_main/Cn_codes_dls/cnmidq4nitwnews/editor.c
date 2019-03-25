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
#include<sys/shm.h>
#include<sys/ipc.h>

struct msg
{
	long type;
	char text[1024];
};

int msgid;

void *rectoChange();

int main() {
	printf("befor popen\n");
	
	int dwfd = fileno(popen("./d","w"));
	
	printf("after popen\n");

	key_t ks=1001;
	msgid=msgget(ks,0666|IPC_CREAT);

//thread to receive the input
	int no=0;
	
	pthread_t tid;
	pthread_create(&tid,NULL,rectoChange,NULL);


	//send , open
	int fd[3];
	printf("inside editor\n");

	char *fifoname[3];
	char *s;
	s = malloc(50);

	for(int i=0;i<3;i++) {
		fifoname[i]=malloc(1024);
		strcpy(fifoname[i],"rep");

		sprintf(s,"%d",i+1);
		strcat(fifoname[i],s);
		
		mkfifo(fifoname[i],0666);
		fd[i]=open(fifoname[i],O_RDWR);
	}

	//doc writer -- popen
	//printf("befor popen\n");
	
	//int dwfd = fileno(popen("./d","w"));
	
	//printf("after popen\n");

	//using poll
	int count=3;

	struct pollfd pfd[count];

	for(int i=0;i<count;i++)
	{
		pfd[i].fd=fd[i];
	//	printf("fd[i] %d\n",fd[i]);
		pfd[i].events=POLLIN;
	}

	int alt=2;

	printf("before while\n");
	while(1)
	{
		printf("count %d\n",count);
		printf("Editorwhile\n");

		int w=poll(pfd,count,-1);
		printf("poll op %d\n",w);
		
		for(int i=0;i<count;i++)
		{
			printf("inside for loop: %d\n",i);

			if(pfd[i].revents==POLLIN)
			{
				printf("FOR %d\n",i);

				int y=read(pfd[i].fd,s,1024);
				printf("received : %s %d\n",s,y);
				//printf("okayy\n");
				if(y>=2 && s[0]=='/' && s[1]=='d')//pass to doc writer the name of fifo
				{
					strcpy(s,fifoname[i]);
					for(;i+1<count;i++)	//eliminate that reporter for editor
					{
						pfd[i]=pfd[i+1];
						fifoname[i]=fifoname[i+1];
					}
					count--;
					printf("sending to DW\n");
					write(dwfd,s,strlen(s));

				}
				else
				{
					//send that msg to news reader


						struct msg ms;
						ms.type=alt;
						char *d;d=malloc(1024);
						strncpy(d,s,y);
						strcpy(ms.text,"\0");
						strcpy(ms.text,d);
						if(ms.text[0] == 'a'){
							ms.type = 3;
							msgsnd(msgid,&ms,sizeof(ms),IPC_NOWAIT);
						}
					
						else{
							struct msg ms;
							ms.type=alt;
							char *d;d=malloc(1024);
							strncpy(d,s,y);
							strcpy(ms.text,"\0");
							strcpy(ms.text,d);
							msgsnd(msgid,&ms,sizeof(ms),IPC_NOWAIT);
						}
					//change the alt for specific news reader
					printf("msg sent to alt : %d\n",alt);

					if(alt == 1)
						alt = 2;
					else if(alt == 2)
						alt = 3;
					else 
						alt = 1;
					//printf("end of else\n");
				}
			}
		}
	}

	//pthread_join(tid,NULL);
}


void *rectoChange()
{
	struct msg mr;

	key_t shmkey = 2000;
	int shmid = shmget(shmkey,sizeof(int),IPC_CREAT | 0666);
	int *x;
	x = (int *)shmat(shmid,(void *)0,0);
	*x = 0;
	printf("\n\n\ninside THREAD\n\n\n");


	// while(1)
	// {
	// 	printf("shared memory part\n");
	// 	int y=msgrcv(msgid,&mr,sizeof(mr),3,0);//receive from 3;
	// 	if(y>0)
	// 	{
	// 		printf("shm mem %d\n",*x);
	// 		*x=*x+1;
	// 		printf("shm mem %d\n",*x);
	// 		printf("shmValChanged\n");

	// 	}
	// }
}