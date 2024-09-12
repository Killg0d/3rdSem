#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct msgbuf1 {
         long    mtype;
         int   num1;
         } message_buf1;
         
typedef struct msgbuf4 {
         long    mtype;
         char    result[10];
         } message_buf4; 
 
 int main()
{
	int msqid;
    int msgflg = IPC_CREAT | 0666;
    key_t key;
    message_buf1 sbuf;
    message_buf4 rbuf;
    
    key = 1234;
    
    if ((msqid = msgget(key, msgflg )) < 0) {
        perror("msgget");
        exit(1);
    }
    // set message type  
    sbuf.mtype = 1;
    printf("Enter the integer ");
    scanf("%d",&sbuf.num1);
     if (msgsnd(msqid, &sbuf, sizeof(int), IPC_NOWAIT) < 0) {
     perror("msgsnd");
        exit(1);
    }
    else
	printf("written successful"); 
    if(msgrcv(msqid, &rbuf, 10, 2, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }
    printf("\n Result received : %s \n",rbuf.result);
    printf("removing message queue \n");
    msgctl(msqid,IPC_RMID,NULL);
    
}
