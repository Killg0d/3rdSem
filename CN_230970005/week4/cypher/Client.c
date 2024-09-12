//tarun
//230970005
//22-8-24
//3.Write a client server program using message queue to cypher the text. Client take input a line of text from the user and sends to server using message Queue. Server reads text from the message queue and cypher the text (cypher method- simple one any of your choice) and return cyphered text to Client for display.
#include "../autoinclude.h"
struct msgbuf
{
	long mtype;
	char mtext[100];
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

	printf("Enter the text to be cyphered:");
	fgets(sbuf.mtext,100,stdin);


	buflen=sizeof(struct msgbuf)-sizeof(long);
	if (msgsnd(msqid, &sbuf, buflen, IPC_NOWAIT) < 0)
	{
		printf ("%d, %ld, %s, %d\n", msqid, sbuf.mtype, sbuf.mtext, buflen);
		die("msgsnd");
	}
	else
		printf("Message Sent");
	if (msgrcv(msqid, &rcvbuf, buflen, 2, 0) < 0)
		die("msgrcv");
	else
	{
		printf("\nCyphered text is:");
		printf("%s", rcvbuf.mtext);
	}
	return 0;

}
