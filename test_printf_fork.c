#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>


int main()
{
	int pid;
	int i = -1;
	while(i < 20)
	{
		i++;
		pid = fork();
		if(pid == 0)
		{
			printf("From Child No = %d\n", i);
			exit(0);
		}
		else
		{
			i++;
			printf("From Parent No =%d\n", i);
			fflush(NULL);
			wait(0);
		}
	}
}