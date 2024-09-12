#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include <strings.h>
#include<string.h>
#define MSGSIZ 63

main(argc,argv)
int argc;
char* argv[];

{
	int fd,j,nwrite;
	char msgbuf[MSGSIZ];
        bzero(msgbuf, MSGSIZ);
	if(argc<2)
	{  
		printf(" Type as - Filename msg1 msg2 ..\n");
		exit(1);	
	}	

	if((fd=open("testpipe1",O_WRONLY))<0)
	{
		printf("pipe open failed in p218\n");
		exit(1);
	}
	printf("FD:%d",fd);
	for(j=1;j<argc;j++)
	{
	 	strcpy(msgbuf,argv[j]);
		if((nwrite=write(fd,msgbuf,MSGSIZ+1))<0)
			printf("pipe wirte failed in p218 \n");
	}
exit(0);
}
