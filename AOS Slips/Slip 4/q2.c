/*Write a C program which creates a child process and child process catches a signal SIGHUP, SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3 seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by displaying message "My Papa has Killed me!!!”.*/


#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pid_t child_pid;

void sighup_handler(int signum){
	printf("Child recevied SIGHUP signal form parent.\n");
}

void sigint_handler(int signum){
	printf("Child recevied SIGHINT signal form parent.\n");
}

void sigquit_handler(int signum){
	printf("Child recevied SIGHQUIT signal form parent and is terminating: My Papa has killed me!!!\n");
	exit(0);
}

int main(){
	if ((child_pid = fork()) == -1){
		perror("fork");
		return 1;
	}
	if(child_pid == 0){
		signal(SIGHUP, sighup_handler);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, sigquit_handler);
	
		while(1){
		}
	}
	else{
		int seconds = 0;
		int max_seconds = 15;
		
		while(seconds < max_seconds){
			sleep(3);
			kill(child_pid, SIGHUP);
			seconds += 3;
		}
		kill(child_pid, SIGQUIT);
		wait(NULL);
	}
	return 0;
}
