//tarun
//230970005
//1/8/2024
//Write a program using pipe to send a string from parent to child in order to
// print number of characters and digits in the string.

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int p[2],pid;
	
	pipe(p);
	pid = fork();
	if(pid==-1)
	{
		perror("Error in forming fork");
		return 1;
	}
	else if( pid >  0 )
	{
		printf("Enter a string:");
		char str[15];
		fgets(str,sizeof(str),stdin);
		
		close(p[0]);
		write(p[1],str,sizeof(str));
	}
	else if(pid == 0)
	{
		close(p[1]);
		char buf[15];
		read(p[0],buf,sizeof(buf));
		int len=0,noch=0,nodgt=0;
		for( len=0;buf[len]!='\0';len++)
		{
			//if(buf[len]>=65 && buf[len] <= 91 || buf[len]>=97 && buf[len]<=123) noch++;
			//else if (buf[len]>=)
			if(isdigit(buf[len]))nodgt++;
			else if(isalpha(buf[len])) noch++;
		}
		printf("Length:%d Char:%d Digits:%d in %s ",len,noch,nodgt,buf);
	}
	else
	{
		/*Empty*/
	}
	return 0;
}
