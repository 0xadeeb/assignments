#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <unistd.h>

struct buffer
{
    long mtype ;
    char mdata[100];
} message ;

void main(){

    key_t key = ftok("ci.c", 0);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    long c_id = 100, t_id = 10;
    float mark, avg;

    for(long i = 1; i <= 5; i++){
        printf("Enter marks of student %ld: ", i);
        scanf("%f", &mark);
        sprintf(message.mdata, "%f", mark);
        message.mtype = i;
        msgsnd(msgid, &message, sizeof(message.mdata), 0);        
        message.mtype = t_id;
        msgsnd(msgid, &message, sizeof(message.mdata), 0);        
    }

    msgrcv(msgid, &message, sizeof(message.mdata), c_id, 0);
    sscanf(message.mdata, "%f", &avg);

    printf("\nMessage received from teaching assistant\nAverage of marks is %.2f\n", avg);

    char grade;
    for(long i = 1; i <= 5; i++){
        msgrcv(msgid, &message, sizeof(message.mdata), c_id, 0);
        sscanf(message.mdata, "%c", &grade);
        printf("Grade of student %ld: %c\n", i, grade);
    }

    msgctl(msgid, IPC_RMID, NULL);

}