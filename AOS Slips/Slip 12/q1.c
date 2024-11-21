/*Write a C program that print the exit status of a terminated child process*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

int main(){
	pid_t child_pid;
	int status;
	
	if((child_pid = fork()) == -1){
		perror("fork");
		return 1;
	}
	
	if(child_pid == 0){
		printf("Child process (PID %d) is running...\n", getpid());
		exit(42);
	}
	
	else{
		wait(&status);
		
		if (WIFEXITED(status)){
			printf("Child process (PID %d) exited with status: %d\n", child_pid, WEXITSTATUS(status));
		}
		
		else{
			printf("Child process (PID %d) did not exit normally\n", child_pid);
		}
	}
	return 0;

}
