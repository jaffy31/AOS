/*8)Write a C program which receives file names as command line arguments and display those filenames in ascending order according to their sizes.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>

int compare(const void * a, const void * b)
{
	struct stat file1_stat, file2_stat;
	stat(*(char**)a, &file1_stat);
	stat(*(char**)b, &file2_stat);
	return (int) (file1_stat.st_size - file2_stat.st_size);
}

int main (int argc, char * argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s file1 file2 file3 ...\n", argv[0]);
		return 1;
	}
	qsort(argv + 1, argc - 1, sizeof(char *), compare);
	
	printf("File names in ascending order of sizes: \n");
	for (int i = 1; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
	return 0;
}

