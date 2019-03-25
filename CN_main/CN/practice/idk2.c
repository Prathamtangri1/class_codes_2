#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

struct mesg{
    long mesg_type;
    char mesg_text[100];
} message;

int main(){
    key_t key;
    int msgid;

    key = ftok("progfile", 65);

    msgid = msgget(key, 0666 | IPC_CREAT);

    msgrcv(msgid, &message, sizeof(message), 1, 0);

    printf("Message received: %s\n", message.mesg_text);

    msgctl(msgid, IPC_RMID, NULL);

    return 0;
}