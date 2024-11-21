/*Write a C program to create 'n' child processes. When all 'n' child processes terminates, Display total cumulative time children spent in user and kernel mode.*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/times.h>

int main(int argc, char * argv[]){
	if (argc != 2) {
		printf("Usage: %s <number_of_child_processes>\n", argv[0]);
		return 1;
	}
	
	int num_children = atoi(argv[1]);
	struct tms start_time, end_time;
	clock_t start_clock, end_clock;
	
	start_clock = times(&start_time);
	
	for (int i = 0; i < num_children; i++){
		pid_t child_pid = fork();
		
		if (child_pid == -1){
			perror("fork");
			return 1;
		}
		
		else if(child_pid == 0){
			printf("Child process %d(PID %d) is running...\n",i+1, getpid());
			exit(0);
		}
	}
	
	for (int i = 0; i < num_children; i++){
		wait(NULL);
	}
	end_clock = times(&end_time);
	printf("Total User Time: %f seconds\n", (double)(end_time.tms_utime-start_time.tms_utime) /sysconf(_SC_CLK_TCK));
	printf("Total System Time: %f seconds\n", (double)(end_time.tms_stime-start_time.tms_stime) /sysconf(_SC_CLK_TCK));
	return 0;
}
