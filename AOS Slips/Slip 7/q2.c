/*Implement the following unix/linux command (use fork, pipe and exec system call) ls –l | wc –l*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
	int pipe_fd[2];
	pid_t ls_pid, wc_pid;
	
	if(pipe(pipe_fd) == -1){
		perror("pipe");
		return 1;
	}
	
	if((ls_pid = fork()) == -1){
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
		
		if (wc_pid == 0) {
			close(pipe_fd[0]);
			dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
		
			execlp("wc", "wc", "-l", NULL);
			perror("execlp wc");
			exit(1);
		}
		else{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			wait(NULL);
			wait(NULL);
		}
	}
	return 0;
}

