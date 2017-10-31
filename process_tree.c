#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
/*
 * Biter BILEN
 * 125001-8
 * 
 * CEng 334 Programming Assignment
 * 
 * n-ary process tree creation.
 * 
 */
int search(int n, pid_t pid, pid_t* pids) {	
	int i;
	for( i = 0; i < n; i++) {
		if (pid == pids[i])
			return 1;
	}
	return 0;
			
}
int main(int argc,char **argv) 
{
	char 	*argp[3]; /* for print_pid args */
	char 	arglevel[10];	
	int 	status, degree, height, level, children;
	int 	i;	
	pid_t 	*pids;
	pid_t 	pid;
	
	if( argc < 3 ) {
		printf("usage: height[int]  degree[int]\n");
                exit(1);	
	}
	else {
		height = atoi(argv[1]);
		degree = atoi(argv[2]);
		if (argc == 3) 
			/* Root is at height 0 */
			level = 1; 
		else
			level = atoi(argv[3]);
	}
	
	for ( i = 0; i < degree; i++ ) {
                pids = (pid_t *) malloc(sizeof(pid_t));
	}
	for ( i = 0; i < 2; i++ ) {
                argp[i] = (char *) malloc(sizeof(char)*10);
	}

	/* Fill in argp for print_pid */
	sprintf(argp[0],"%s","print_pid");
	sprintf(argp[1],"%d",level); 
	argp[2] = NULL;

	/* for leaf nodes */
	if ( level == height ) {
		sprintf(argp[1],"%d",level); 
		execv("print_pid",argp);
		return 0;
	}
	
	/* Fill in argv for process_tree */
	sprintf(argv[0],"%s","process_tree");
	sprintf(arglevel,"%d",level+1); 
	argv[3] = arglevel;
	argv[4] = NULL;
	
	/* for others */
	for ( i = 0; i < degree; i++ ) {
		/* Fork  error */
		if((pids[i] = fork()) < 0) {
			i--;
			continue;
		}
		/* Child */
		else if ( pids[i] == 0 ) {
			execv("process_tree",argv);
			/* the following code is only executed if the above execv fails */
			perror("execv");
			exit(EXIT_FAILURE);						
		}
		/* Parent */
		else {
			continue;
		}
	}
	/* Parent */
	for ( i = 0; i < degree; i++) {
		printf("%d\t",pids[i]);
	}
	for ( i = 0; i < degree; i++) {
		pid = wait(&status);
		if (WIFEXITED(status) && search(degree,pid,pids)); 
		else {
			i--;
			printf("Error in waiting.\tTrying again...");
		}
			
	}
	execv("print_pid", argp);
	/* the following code is only executed if the above execv fails */
	perror("execv");
	exit(EXIT_FAILURE);
	return 0;
}

