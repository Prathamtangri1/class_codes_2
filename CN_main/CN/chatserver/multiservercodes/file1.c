#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(){
	int fd;
	
	char* fifo_pub = "./fifo_public";
	mkfifo(fifo_pub, 0666);
	
	int clients[80], data_in[80], data_center[3];
	int client_count = 0;
	
	data_center[0] = 0;
	data_center[1] = 0;
	data_center[2] = 0;
	
	FILE* fddir[3];
	int d2p[80][2];
	
	char fifo_pri[80][20];
	
	while(1){
		fd = open(fifo_pub, O_RDONLY);
		read(fd, data_in, sizeof(data_in));
		client_count++;
		
		int dir = data_in[1];
		dir--;
		clients[client_count] = dir;
		
		if(data_center[dir] == 0){
			char str[20];
			sprintf(str, "./d%d.exe", dir);
			fddir[dir] = popen(str, "r");
			data_center[dir] = 1;
		} 
		
		char fifo_pri[client_count][20];
		sprintf(fifo_pri[client_count], "./fifo_pri_%c", data_in[0]);
		mkfifo(fifo_pri[client_count], 0666);
		
		pipe(d2p[client_count]);
		
		dup2(fddir[dir], d2p[client_count][1]);
		close(fd);
	}

	for(int i = 0 ; i < 3 ; i++) {
		if(data_center[i] == 1)
			close(fddir[i]);
	}
	
	for(int i = 0 ; i < client_count ; i++) {
		close(d2p[i]);
	}
	
	return 0;
}

//	pid_t cpid[3];
//	int pp[3][2];

/*
			pipe[pp[dir]];
			cpid[dir] = fork();
			
			if(cpid[dir] == -1){
				perror("Data center creation failed");
				exit(1);
			}	
			else if(cpid[dir] > 0){
				
			}
			else{
				close(pp[dir][0];
				dup2(pp[dir][1], 1);
			
			}
		*/
