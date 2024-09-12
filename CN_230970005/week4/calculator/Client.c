//tarun
//230970005
//22-8-24
//2.Write a client server program using message queue to simulate calculator operations (+, -, *, / between two numbers). Client accepts two numbers and operation to be performed from the user and writes to message queue. Server reads from message queue and performs the required operation to produce result. The server returns the result to client using message queue in order to display result.
#include "../autoinclude.h"

struct msgbuf//to send
{
	long mtype;
	int num1;
	int num2;
	char op;
};
struct msgrcv//to recieve
{
	long mtype;
	int result;
};
int main()
{
	int msqid;
	int msgflg = IPC_CREAT | 0666;
	key_t key;
	struct msgbuf sbuf;
	struct msgrcv rcvbuf;
	size_t buflen;
	key=12345;
	if ((msqid = msgget(key, msgflg )) < 0) //Get the message queue ID for the given key
		die("msgget");
	sbuf.mtype = 1;
	
	printf("Enter number1:");
	scanf("%d",&sbuf.num1);
	printf("Enter number2:");
	scanf("%d",&sbuf.num2);
	fflush(stdin);
	printf("Enter operator:");
	scanf(" %c",&sbuf.op);
	buflen=sizeof(struct msgbuf)-sizeof(long);
	if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
	{
		//printf ("%d, %ld, %d, %d\n", msqid, sbuf.mtype, sbuf.num1, buflen);
		die("msgsnd");
	}
	else
		printf("Message Sent");
	if (msgrcv(msqid, &rcvbuf, sizeof(int), 2, 0) < 0){
		die("msgrcv");
	}
	else
		printf("Recieved");
	printf("\nResult is:");
	printf("%d\t", rcvbuf.result);
	
	return 0;
}
