/*10)Display all the files from current directory whose size is greater that n Bytes Where n
is accept from user.*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#include<dirent.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <size_in_bytes>\n", argv[0]);
		return 1;
	}
	long long int min_size = atoll(argv[1]);
	DIR *dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return 1;
	}
	struct dirent * entry;
	
	printf("Files with size greater than %lld bytes\n", min_size);
	
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			struct stat file_stat;
			if (stat(entry->d_name, &file_stat) == 0)
			{
				if (file_stat.st_size > min_size)
				{
					printf("%s\n", entry->d_name);
				}
				
			}
		}
	}
	closedir(dir);
	return 0;
}






