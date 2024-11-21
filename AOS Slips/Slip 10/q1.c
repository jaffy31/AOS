/*Write a program that illustrates how to execute two commands concurrently with a pipe.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child1_pid, child2_pid;

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    if ((child1_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }
    if (child1_pid == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
        execlp("ls", "ls", NULL);
        perror("execlp ls");
        exit(1);
    } else {
        if ((child2_pid = fork()) == -1) {
            perror("fork");
            return 1;
        }

        if (child2_pid == 0) {
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
            execlp("wc", "wc", "-l", NULL);
            perror("execlp wc");
            exit(1);
        } else {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}

