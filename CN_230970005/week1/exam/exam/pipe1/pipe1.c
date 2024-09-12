#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{
	int f,sum=0,pd2[2],pd[2],pid,nread,a[5];
	pipe(pd);
	pipe(pd2);
	pid=fork();
	if(pid<0)
	{
		perror("Error in creating pipes");
		exit(1);
	}
	if(pid>0)
	{
		printf("Enter 5 nos:\n");
		for(int i=0;i<5;i++)
			scanf("%d",&a[i]);
		close(pd[0]);
		close(pd2[1]);
		write(pd[1],&a,sizeof(a));
		read(pd2[0],&sum,sizeof(sum));
		printf("\nSum is %d",sum);
	}
	else
	{
		close(pd[1]);
		close(pd2[0]);
		read(pd[0],&a,sizeof(a));
		printf("\nFive nos are:");
		for(int i=0;i<5;i++)
			sum+=a[i];
		write(pd2[1],&sum,sizeof(sum));
	}
	printf("\n");
	return 0;
}
