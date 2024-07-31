#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	pid_t pid;
	int x=11;

	pid =fork();
	if(pid!=0)
	{
		printf("parent: x=%d\n",--x);
		exit(0);	
	}
	else
	{
		printf("child: x=%d\n",++x);
		exit(0);
	}
	return 0;


}
 
