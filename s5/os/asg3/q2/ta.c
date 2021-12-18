#include <stdio.h>
#include <sys/ipc.h> 
#include <sys/msg.h> 
#include <unistd.h>

struct buffer
{
    long mtype ;
    char mdata[100] ;
} message ;

char calGrade(float mark){
    if(mark >= 40)
        return 'S';
    else if(mark >= 30)
        return 'A';
    else if(mark >= 20)
        return 'B';
    else
        return 'E';
}

void main(){

    key_t key = ftok("ci.c", 0);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    char grade[5];
    float marks[5], avg = 0;
    long t_id = 10, c_id = 100;

    for(long i = 1; i <= 5; i++){
        msgrcv(msgid, &message, sizeof(message), t_id, 0);
        sscanf(message.mdata, "%f", &marks[i-1]);
        avg += marks[i-1];
        grade[i-1] = calGrade(marks[i-1]);
    }

    avg /= 5;

    message.mtype = c_id; 
    sprintf(message.mdata, "%2f", avg);
    msgsnd(msgid, &message, sizeof(message.mdata), 0);

    for(long i = 0; i < 5; i++){
        sprintf(message.mdata, "%c", grade[i]);
        msgsnd(msgid, &message, sizeof(message.mdata), 0);
    }

    printf("Average and Grades send to Couse Instructor\n");
}