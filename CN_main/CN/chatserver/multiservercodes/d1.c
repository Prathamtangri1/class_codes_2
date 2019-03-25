#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

int main(){
	while(1){
		for(int i = 0 ; i < 26 ; i++){
			printf("\nD1, %d\n", i);
		}
	}
	return 0;


}
