/*6)Write a C program that a string as an argument and return all the files that begins with
that name in the current directory.For example > ./a.out foo will return all file names
that begins with foo*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>

int main (int argc, char * argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <string>\n", argv[0]);
		return 1;
	}
	DIR * dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return 1;
	}
	const char * search_string = argv[1];
	size_t search_length = strlen(search_string);
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			if (strncmp(entry->d_name, search_string, search_length) == 0) 
			{
				printf("%s\n", entry->d_name);
			}
		}
	}
	closedir(dir);
	return 0;
}
