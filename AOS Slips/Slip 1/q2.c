/*Write a C program to send SIGALRM signal by child process to parent process and parent process make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep system call)*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pid_t child_pid;

void sigalrm_handler(int signum){
	printf("ALarm is fired.\n");
}

int main(){
	signal(SIGALRM, sigalrm_handler);
	
	if ((child_pid = fork()) == -1){
		perror("fork");
		return 1;
	}
	
	if(child_pid == 0){
		sleep(3);
		kill(getpid(), SIGALRM);
		exit(0);
	}
	else{
		while(1){
		}
	}
	return 0;
}
