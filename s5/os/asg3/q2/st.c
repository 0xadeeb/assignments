#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <unistd.h>

struct buffer
{
    long mtype ;
    char mdata[100] ;
} message ;

void main()
{
    key_t key = ftok("ci.c", 0);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    float mark;
    for(long i = 1; i <= 5; i++){

        msgrcv(msgid, &message, sizeof(message), i, 0);
        sscanf(message.mdata, "%f", &mark);
        printf("Student %ld scored %.2f marks\n", i, mark);
    }
    
}