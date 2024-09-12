//tarun
//230970005
//22-8-24
//3.Write a client server program using message queue to cypher the text. Client take input a line of text from the user and sends to server using message Queue. Server reads text from the message queue and cypher the text (cypher method- simple one any of your choice) and return cyphered text to Client for display.
#include "../autoinclude.h"
#include "string.h"
struct msgbuf
{
	long mtype;
	char mtext[100];
};
char* cypher(char* msg)
{
	for(int i=0;msg[i]!='\0';i++)
	{
		msg[i]+= 5;
	}
	return msg;
}
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

	strcpy(rcvbuf.mtext,cypher(rcvbuf.mtext));
	printf("\n%s\n",rcvbuf.mtext);

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
