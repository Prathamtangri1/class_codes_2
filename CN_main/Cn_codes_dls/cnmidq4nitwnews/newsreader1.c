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
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include<signal.h>
int flag=0;
int count=0;

struct msg
{
	long type;
	char text[1024];
};


int getPort(char *s)
{
	int x=0;

	for(int i=0;s[i]!='\0' && s[i]>='0' && s[i]<='9' ; i++)
	{
		x=x*10+s[i]-'0';
	}
	return x;
}

int start()
{
	count=-1;
	printf("making count -1\n");
	signal(SIGUSR1,start);
}
int end()
{
	count=0;
	printf("making count 0\n");
	signal(SIGUSR2,end);
}


int main()
{

	signal(SIGUSR1,start);
	signal(SIGUSR2,end);

	char *fifoname;
	fifoname=malloc(100);
	strcpy(fifoname,"N1");
	mkfifo(fifoname,0666);
	int ffd=open(fifoname,O_RDWR); //fifo fd

	printf("ffd %d\n",ffd);

	key_t ks=1001;
	int msgid=msgget(ks,0666|IPC_CREAT);
	struct msg mr;
	mr.type=4;
	sprintf(mr.text,"%d",getpid());
	msgsnd(msgid,&mr,sizeof(mr),0);
	char *s;s=malloc(1024);

	//get pid of that nr
	int y=msgrcv(msgid,&mr,sizeof(mr),6,0);
	strncpy(s,mr.text,y);
	int pid=atoi(s);
    

	while(1)
	{
		printf("while\n");
		int y=msgrcv(msgid,&mr,sizeof(mr),1,0);
		if(y<=0) continue;

		while(count==-1); //stay till count is -1

        strcpy(s,mr.text);
        printf("received %s\n",s);


        if(s[0]>='0' && s[0]<='9') //decimal number //connect to server
        {

            kill(pid,SIGUSR1);

            mr.type=3;
            msgsnd(msgid,&mr,sizeof(mr),0);
            printf("msg sent to editor\n");
            int port=getPort(s);
            struct sockaddr_in servaddr;
            int sfd;
            char buffer[1024];

            servaddr.sin_family = AF_INET;
            servaddr.sin_port = htons(port);
            servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");


            if((sfd = socket(AF_INET,SOCK_STREAM,0))<0)
            {

            printf("error in creation of socket\n");
            return 0;
            }


            if(connect(sfd, (struct sockaddr *)&servaddr,sizeof(servaddr))<0)
            {
            printf("connection failed\n");
            printf("errno %d \n",errno);

            }

            char *s;
            while(1) //receive from live telecast
            {	
            int y=recv(sfd,buffer,1024,0);
            //write to fifo
            if(y>0 && buffer[0]=='-') //send
            {
        //		signal()
            break;
            }
            s=malloc(100);
            strncpy(s,buffer,y);
            write(ffd,s,y);
            }

            kill(pid,SIGUSR2);
        }
        else
        {
        //send it to screen
        write(ffd,s,y);
        
        }



	}
}
