/*Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the appropriate message and exits on pressing ctrl-c again.*/


#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
int ctrlc_count = 0;

void sigint_handler(int signum){
	if(ctrlc_count == 0){
		printf("\nTest Complete.\n");
		printf("\nPress Ctrl-C again to exit.\n");
		ctrlc_count++;
	}
	else{
		printf("\nExiting...\n");
		exit(0);
	}
}

int main(){
	signal(SIGINT, sigint_handler);
	printf("\nPress Ctrl-C to test the signal handler.\n");
	while(1){
		
	}
	return 0;
}

