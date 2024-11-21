/*Write a C program that illustrates suspending and resuming processes using signals.*/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pid_t child_pid;

void sigusr1_handler(int signum){
	printf("Child process resumed.\n");
}

void sigusr2_handler(int signum){
	printf("Child process suspended.\n");
}

int main(){
	if ((child_pid = fork()) == -1){
		perror("fork");
		return 1;
	}
	
	if(child_pid == 0){
		signal(SIGUSR1, sigusr1_handler);
		signal(SIGUSR2, sigusr2_handler);
		
		while(1){
		}
	}
	else{
		int choice;
		
		printf("1. Suspend child process (send SIGUSR2)\n");
		printf("2. Suspend child process (send SIGUSR1)\n");
		printf("3.Exit\n");
		while(1){
			printf("Enter your choice: ");
			scanf("%d", &choice);
			switch(choice){
				case 1:
					kill(child_pid, SIGUSR2);
					break;
				case 2:
					kill(child_pid, SIGUSR1);
					break;
				case 3:
					kill(child_pid, SIGKILL);
					return 0;
				default:
					printf("Invalid choice. Try again.\n");
			}
		}
	}
	return 0;
}


