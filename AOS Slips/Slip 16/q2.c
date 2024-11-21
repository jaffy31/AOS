/*Write a C program which create a child process which catch a signal sighup, sigint and sigquit. The Parent process send a sighup or sigint signal after every 3 seconds, at the end of 30 second parent send sigquit signal to child and child terminates my displaying message “My DADDY has Killed me!!!”.*/

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
	printf("Child recevied SIGHQUIT signal form parent and is terminating: My DADDY has killed me!!!\n");
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
		int max_seconds = 30;
		
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
