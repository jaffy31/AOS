/*Write a C program to get and set the resource limits such as files, memory associated with a process*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/resource.h>

int main() {
	struct rlimit limit;
	
	if (getrlimit(RLIMIT_NOFILE, &limit) == 0){
		printf("Current Maximum Number of Open File (soft limit): %lu\n", (unsigned long) limit.rlim_cur);
	}
	
	else{
		perror("getrlimit");
		return 1;
	}
	limit.rlim_cur = 10000;
	
	if (setrlimit(RLIMIT_NOFILE, &limit) == 0){
		printf("New Maximum Number of Open File (soft limit): %lu\n", (unsigned long) limit.rlim_cur);
	}
	
	else{
		perror("setrlimit");
		return 1;
	}
	
	if (getrlimit(RLIMIT_AS, &limit) == 0){
		printf("Current Maximum Memory Size (soft limit): %lu\n", (unsigned long) limit.rlim_cur);
	}
	
	else{
		perror("getrlimit");
		return 1;
	}
	limit.rlim_cur = 512 * 1024 * 1024;
	
	if (setrlimit(RLIMIT_AS, &limit) == 0){
		printf("New Maximum Memory Size (soft limit): %lu\n", (unsigned long) limit.rlim_cur);
	}
	
	else{
		perror("setrlimit");
		return 1;
	}
	
	return 0;
	
}
