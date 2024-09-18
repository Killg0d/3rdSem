//tarun
//cn
//file to copy files
//25-07-24
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int main()
{
	printf("\nGet input filename from user:");
	char filename1[20];
	scanf("%s",filename1);
	
	printf("\nGet output filename from user:");
	char filename2[20];
	scanf("%s",filename2);

	int flags =O_RDONLY;
	int fd =open(filename1,flags);
	if(fd==-1)
	{
		perror("Error opening file");
		return 1;
	}	
	
	char buffer[100];
	ssize_t bytesRead;
	
	bytesRead = read(fd, buffer, sizeof(buffer));
	if (bytesRead == -1) {
	perror("Error reading from stdin");
	return 1;
	}
	
	buffer[bytesRead] = '\0';
	printf("Read from stdin: %s\n", buffer);
	
	close(fd);
	int flag= O_WRONLY|O_CREAT;
	int fw =open(filename2,flag,00700);
	if(fw==-1)
	{
		perror("Error opening file");
		return 1;
	}
	ssize_t bytesWrite=write(fd,buffer,sizeof(buffer));
	
	
	return 0;
	
	
		
}
