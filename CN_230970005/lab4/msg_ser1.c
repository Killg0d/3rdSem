#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

typedef struct msgbuf2 {
         long    mtype;
         int    num2;
         } message_buf2;

typedef struct msgbuf3 {
         long    mtype;
         char    result[10];
         } message_buf3;    
int main()
{
    int i,j,temp,num;
    int msqid;
    key_t key;
    message_buf2  rbuf;
    message_buf3  sbuf;
    int msgflg = IPC_CREAT | 0666;

    key = 1234;

    if ((msqid = msgget(key, 0666)) < 0){
     perror("msgget");
        exit(1);
    }
    if(msgrcv(msqid, &rbuf, sizeof(int), 1, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }
    printf("\n Integer received : ");
    printf("%d \n",rbuf.num2);
      //set message type
      sbuf.mtype=2;
     if(rbuf.num2%2==0)
       strcpy(sbuf.result,"even");
     else
     	strcpy(sbuf.result,"odd");
    if (msgsnd(msqid, &sbuf, sizeof(sbuf.result), IPC_NOWAIT) < 0) {
     perror("msgsnd");
        exit(1);
    }
    else
	printf("written successful \n"); 
    
    exit(0);
  
  }
    
