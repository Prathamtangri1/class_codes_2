#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

//Pipes
/* int main(){
    int pp[2];
    pipe(pp);

    pid_t p = fork();
    if(p == -1){
        printf("fail!!!");
        exit(1);
    }
    else if (p == 0){
        printf("child");
        close(pp[0]);
        char str[80];
        scanf("%s", str);
        write(pp[1], str, strlen(str)+1);
    }
    else{
        printf("parent");
        close(pp[1]);
        char str[80];
        int nbytes = read(pp[0], str, sizeof(str));
        printf("\nHere is what the child says: ");
        printf("%s", str);
    }

} */

//Message Qs
/* struct mesg{
    long mesg_type;
    char mesg_text[100];
} message;

int main(){
    key_t key;
    int msgid;

    key = ftok("mesgq1", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);

    message.mesg_type = 1;

    printf("Write data: ");
    gets(message.mesg_text);

    msgsnd(msgid, &message, sizeof(message), 0);

    printf("\nMessage sent\n");

    return 0;
}
 */
