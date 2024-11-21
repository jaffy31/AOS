/*7)Read the current directory and display the name of the files, no of files in current
directory*/

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>

int main()
{
	DIR * dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return	1;
	}
	int file_count = 0;
	printf("Files in the current directory\n");
	struct dirent* entry;
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			printf("%s\n", entry->d_name);
			file_count++;
		}
	}
	closedir(dir);
	printf("\nNumber of files in the current directory: %d\n", file_count);
	return 0;
}

