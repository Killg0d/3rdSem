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
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	struct msgbuf rcvbuf,sbuf;
	size_t buflen;
	key=1234;
	if ((msqid = msgget(key, msgflg )) < 0) //Get the message queue ID for the given key
		die("msgget");
	sbuf.mtype = 1;
	
	printf("Enter the size of array:");
	scanf("%d",&sbuf.size);
	printf("Enter the elements:");
	for(int i=0;i<sbuf.size;i++)
		scanf("%d",&sbuf.mtext[i]);
	buflen=sizeof(struct msgbuf)-sizeof(long);
	if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
	{
		printf ("%d, %ld, %d, %d\n", msqid, sbuf.mtype, sbuf.mtext[0], buflen);
		die("msgsnd");
	}
	else
		printf("Message Sent");
	if (msgrcv(msqid, &rcvbuf, buflen, 2, 0) < 0)
		die("msgrcv");
	printf("\nSorted Array is:");
	for(int i=0;i<rcvbuf.size;i++)
		printf("%d\t", rcvbuf.mtext[i]);
	return 0;
}
