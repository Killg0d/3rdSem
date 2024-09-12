#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
int main()
{
	
	int fd,p,pd;
	p=mkfifo("Clientfifo",0666);
	if(p<0)
	{
		perror("Pipe creation failed");
		exit(1);
	}
	pd=open("Clientfifo",O_RDWR);
	if(pd<0)
	{
		perror("Pipe opening failed");
		exit(1);
	}
	char fname[50];
	read(pd,fname,sizeof(fname));
	printf("File name is: %s",fname);
	printf("\n");
	char content[100];
	if(access(fname,F_OK)!=-1)
	{
		fd = open(fname,O_RDONLY);
		read(fd,content,sizeof(content));
	}
	else
		strcpy(content,"File does not exist\n");
	write(pd,content,sizeof(content));
	unlink("Clientfifo");
	return 0;
}
