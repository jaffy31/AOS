/*2)Take multiple files as command line arguments and print their inode number and file types*/


#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: No files name provided.\n");
        printf("Usage: %s file1 file2 file3...\n", argv[0]);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        const char *filename = argv[i];
        struct stat filestat;

        if (stat(filename, &filestat) == 0) {
            printf("File: %s\n", filename);
            printf("Inode Number: %lu\n", (unsigned long)filestat.st_ino);

            if (S_ISREG(filestat.st_mode)) {
                printf("%s is regular file\n",argv[1]);
            } else if (S_ISDIR(filestat.st_mode)) {
                printf("%s is a directory\n",argv[1]);
            } else if (S_ISCHR(filestat.st_mode)) {
                printf("%s is a character device\n",argv[1]);
            } else if (S_ISBLK(filestat.st_mode)) {
                printf("%s is a block device\n",argv[1]);
            } else if (S_ISFIFO(filestat.st_mode)) {
                printf("%s is a named pipe\n",argv[1]);
            } else if (S_ISLNK(filestat.st_mode)) {
                printf("%s is a symbolic link\n",argv[1]);
            } else if (S_ISSOCK(filestat.st_mode)) {
                printf("%s is a socket\n",argv[1]);
            }
        } else {
            printf("Error: Could not retrieve information for %s\n", filename);
        }

        printf("\n");
    }

    return 0;
}

