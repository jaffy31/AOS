/*Write a C program to implement the following unix/linux command (use fork, pipe and exec system call). Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution. i. Ls –l | wc –l*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

void block_signals(int signum){
	printf("Signal %d recevied but blocked.\n", signum);
}

int main(){
	signal(SIGINT, block_signals);
	signal(SIGQUIT, block_signals);
	
	int pipe_fd[2];
	pid_t ls_pid, wc_pid;
	
	if (pipe(pipe_fd) == -1){
		perror("pipe");
		return 1;
	}
	
	if ((ls_pid = fork()) == -1){
		perror("fork");
		return 1;
	}
	
	if (ls_pid == 0){
		close(pipe_fd[1]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		
		execlp("ls", "ls", "-l", NULL);
		perror("execlp ls");
		exit(1);
	}
	else{
		if ((wc_pid = fork()) == -1){
			perror("fork");
			return 1;
		}
		
		if (wc_pid == 0){
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDOUT_FILENO);
			close(pipe_fd[0]);
		
			execlp("wc", "wc", "-l", NULL);
			perror("execlp wc");
			exit(1);
		}
		else{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			
			waitpid(ls_pid, NULL, 0);
			waitpid(wc_pid, NULL, 0);
		}
	}
	return 0;
}
