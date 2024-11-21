/*9)Display all the files from current directory which are created in particular month*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<time.h>
#include<dirent.h>
#include<string.h>

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <month>\n", argv[0]);
		return 1;
	}
	char * target_month = argv[1];
	
	DIR *dir = opendir(".");
	if (dir == NULL)
	{
		perror("opendir");
		return 1;
	}
	struct dirent * entry;
	struct tm file_time;
	char file_month[3];
	printf("Files created in month %s\n", target_month);
	
	while ((entry = readdir(dir)) != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			struct stat file_stat;
			if (stat(entry->d_name, &file_stat) == 0)
			{
				localtime_r(&file_stat.st_ctime, &file_time);
				strftime(file_month, sizeof(file_month),"%m", &file_time);
				if (strcmp(file_month,target_month) == 0)
				{
					printf("%s\n", entry->d_name);
				}
				
			}
		}
	}
	closedir(dir);
	return 0;
}






