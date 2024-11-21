/*Write a C program that redirects standard output to a file output.txt. (use of dup and open system call).*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main (){
	int file_descriptor = open("output.txt", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (file_descriptor == -1){
		perror("open");
		return 1;
	}
	
	if (dup2(file_descriptor, STDOUT_FILENO) == -1){
		perror("dup2");
		return 1;
	}
	
	printf("This is an example of standard output redirection using the 'dup' and 'open' system calls.\n");
	printf("The ouput is redirected to the 'output.txt file'.\n");
	return 0;

}



