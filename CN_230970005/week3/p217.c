#include<fcntl.h>
#include<stdio.h>
#include <strings.h>
#include<errno.h>
#define MSGSIZ 63

main()
{
 	int fd;
	char msgbuf[MSGSIZ+1];
	int n;
	bzero(msgbuf, MSGSIZ);

	if(( fd=open("testpipe1",O_RDWR))<0)
		perror("pipe open failed  in p217\n");
	for(;;)
	{
		if((n=read(fd,msgbuf,MSGSIZ+1))>0)
			printf(" Message Received %s \n",msgbuf);
	}
}

