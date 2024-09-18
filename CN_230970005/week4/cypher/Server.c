//tarun
//230970005
//22-8-24
//1.Write a client server program using message queue to sort array of elements. Client takes input from user a set of integers and send to server using message queue for sorting. The server reads message queue and return sorted array to client for displaying at client.
#include "../autoinclude.h"

typedef struct msgbuf
{
	long mtype;
	int size;
	int mtext[100];
};
int main()
{
	int msqid;
	key_t key;
	struct msgbuf rcvbuf;
	key = 1234;
	if ((msqid = msgget(key, 0666)) < 0)
		die("msgget()");
	//Receive an answer of message type 1.
	/* Syntax : ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int
	msgflg); */
	size_t buflen=sizeof(rcvbuf)-sizeof(long);
	if (msgrcv(msqid, &rcvbuf, buflen, 1, 0) < 0)
		die("msgrcv");
	for(int i=0;i<rcvbuf.size;i++)
        {
            for(int j=rcvbuf.size-1;j>i;j--)
            {
                if(rcvbuf.mtext[i]>rcvbuf.mtext[j])
                {
                    int temp=rcvbuf.mtext[i];
                    rcvbuf.mtext[i]=rcvbuf.mtext[j];
                    rcvbuf.mtext[j]=temp;
                }
            }
        }
        rcvbuf.mtype=2;
        if (msgsnd(msqid, &rcvbuf, buflen, IPC_NOWAIT) < 0)
	{
		printf ("%d, %ld, %d, %d\n", msqid, rcvbuf.mtype, rcvbuf.mtext[0], buflen);
		die("msgsnd");
	}
	else
		printf("Message Sent");
	
	exit(0);
}
