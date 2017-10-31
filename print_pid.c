#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(int argc,char ** argv) 
{
	printf("Process %d from level %d is terminating ...\t Its parent process is:%d.\n",getpid(),atoi(argv[1]),getppid());	
	return 0;
}

	
