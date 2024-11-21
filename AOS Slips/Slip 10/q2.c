/*Generate parent process to write unnamed pipe and will read from it*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

int main(){
	int pipe_fd[2];
	pid_t child_pid;
	char message[]="Hello, Child !..";
	if(pipe(pipe_fd)==-1){
		perror("pipe");
		return 1;
	}
	if((child_pid=fork())==-1){
		perror("pipe");
		return 1;
	}
	if(child_pid == 0){
		close(pipe_fd[1]);
		char buffer[256];
		ssize_t bytes_read = read(pipe_fd[0],buffer,sizeof(buffer));
		if(bytes_read == -1){
			perror("read");
			return 1;
		}
		printf("Child recieved %s\n",buffer);
		close(pipe_fd[0]);
	}
	else{
		close(pipe_fd[0]);
		ssize_t bytes_written=write(pipe_fd[1],message,strlen(message));
		
		if(bytes_written==-1){
			perror("write");
			return 1;
		}
		close(pipe_fd[1]);
		wait(NULL);
	}
	return 0;
}



