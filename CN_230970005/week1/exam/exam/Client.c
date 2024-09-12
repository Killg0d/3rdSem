#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main()
{
	char content[100];
	int fd,p,pd;
	pd=open("Clientfifo",O_RDWR);
	if(pd<0)
	{
		perror("Pipe opening failed");
		exit(1);
	}
	char fname[50];
	printf("Enter a file name:");
	scanf("%s",fname);
	write(pd,fname,sizeof(fname));
	sleep(10);
	read(pd,content,sizeof(content));
	printf("\nContent:%s",content);
	return 0;
}
