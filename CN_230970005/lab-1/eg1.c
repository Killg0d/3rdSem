#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	pid_t pid;
	int x=11;
	printf("%d and %d",getpid(),getppid());
	pid =fork();
	if(pid!=0)
	{
		printf("parent: x=%d\n",--x);
		exit(0);
		printf("%d",pid);	
	}
	else
	{
		printf("child: x=%d and %d",getpid(),getppid());
		exit(0);
	}
	return 0;


}
 
