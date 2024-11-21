/*Write a C program which creates a child process to run linux/ unix command or any user defined program. The parent process set the signal handler for death of child signal and Alarm signal. If a child process does not complete its execution in 5 second then parent process kills child process*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pid_t child_pid;

void sigchld_handler(int sigum){
	int status;
	pid_t terminated_pid;
	terminated_pid = wait(&status);
	
	
	if (WIFEXITED(status)){
		printf("Child process with PID %d terminated normally with exit status %d\n", terminated_pid, WEXITSTATUS(status));
	}
	
	else if(WIFSIGNALED(status)){
		printf("Child process with PID %d terminated by signal %d\n", terminated_pid, WTERMSIG(status));
	}
}

void sigalarm_handler(int signum){
	printf("Child process exceeded the limit and is killed.\n");
	kill(child_pid, SIGKILL);
	
}

int main(){
	signal(SIGCHLD, sigchld_handler);
	signal(SIGALRM, sigalarm_handler);
	
	if ((child_pid = fork()) == -1){
		perror("fork");
		return 1;
	}
	
	if (child_pid == 0){
		execlp("ls", "ls", "-l", NULL);
		perror("execlp");
		exit(1);
	}
	else{
		alarm(5);
		pause();
	}
	return 0;
}
