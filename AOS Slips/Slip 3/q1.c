/*Print the type of file and inode number where file name accepted through Command Line*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
void print_file_type(mode_t st_mode) {
    if (S_ISREG(st_mode)) {
        printf("File Type: Regular File\n");
    } else if (S_ISDIR(st_mode)) {
        printf("File Type: Directory\n");
    } else if (S_ISLNK(st_mode)) {
        printf("File Type: Symbolic Link\n");
    } else if (S_ISCHR(st_mode)) {
        printf("File Type: Character Device\n");
    } else if (S_ISBLK(st_mode)) {
        printf("File Type: Block Device\n");
    } else if (S_ISFIFO(st_mode)) {
        printf("File Type: FIFO (Named Pipe)\n");
    } else if (S_ISSOCK(st_mode)) {
        printf("File Type: Socket\n");
    } else {
        printf("File Type: Unknown\n");
    }
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_name>\n", argv[0]);
        return 1;
    }
    struct stat file_stat;
    if (stat(argv[1], &file_stat) == -1) {
        perror("stat");
        return 1;
    }
    printf("Inode Number: %ld\n", (long)file_stat.st_ino);
    print_file_type(file_stat.st_mode);
    return 0;
}
