#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int fd[2];

    pid_t pid;

    pipe(fd);

    if (pipe < 0) {
        printf("Fail to Create pipe\n");
    }

    pid = fork();

    if (pid < 0) {
        printf("fork() Error\n");
        exit(1);
    } else if (pid == 0) {
        close(fd[0]);

        printf("child process\n");
        struct timeval start_time;

        gettimeofday(&start_time, NULL);

        write(fd[1], &start_time, sizeof(start_time) + 1);
        sleep(1);

        execvp(argv[1], &argv[1]);
        
        close(fd[1]);
        exit(0);
    } else {
        wait(NULL);
        close(fd[1]);

        printf("parent process\n");
        struct timeval start_time, end_time;

        read(fd[0], &start_time, sizeof(start_time) + 1);

        printf("start_time - %ld\n", start_time.tv_sec);

        gettimeofday(&end_time, NULL);

        printf("end_time - %ld\n", end_time.tv_sec);

        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000;

        printf("elapsed_time : %fs\n", elapsed_time);

        close(fd[0]);
        exit(0);
    }

    return 0;
}