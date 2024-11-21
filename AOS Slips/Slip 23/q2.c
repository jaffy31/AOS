/*Write a C program to Identify the type (Directory, character device, Block device, Regular file, FIFO or pipe, symbolic link or socket) of given file using stat() system call.*/


#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(int argc, char **argv){
	if (argc < 2){
		printf("No file name passed\n");
		exit(0);
	}

	struct stat filestat;

	if (stat(argv[1], &filestat)<0){
		perror("Stat");
		return 1;
	}

	if (S_ISREG(filestat.st_mode)){
		printf("%s is a regular file\n",argv[1]);
	}

	else if (S_ISDIR(filestat.st_mode)){
		printf("%s is a directory\n",argv[1]);
	}

	else if (S_ISCHR(filestat.st_mode)){
		printf("%s is a character device\n",argv[1]);
	}

	else if (S_ISBLK(filestat.st_mode)){
		printf("%s is a block device\n",argv[1]);
	}

	else if (S_ISFIFO(filestat.st_mode)){
		printf("%s is a named pipe\n",argv[1]);
	}

	else if (S_ISLNK(filestat.st_mode)){
		printf("%s is a symbolic link\n",argv[1]);
	}

	else if (S_ISSOCK(filestat.st_mode)){
		printf("%s is a socket\n",argv[1]);
	}
	return 0;

}
