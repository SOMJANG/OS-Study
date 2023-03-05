#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>


int main(int argc, char* argv[]) {
    pid_t pid;
    
    const int SIZE = sizeof(struct timeval);
    const char *name = "time";
    
    int fd;

    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);

    struct timeval *start_time;
    start_time = (struct timeval *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    pid = fork();

    if (pid < 0) {
        printf("fork() Error\n");
        exit(1);
    } else if (pid == 0) {
        printf("child process\n");

        gettimeofday(start_time, NULL);
        // execlp("/bin/ls","ls", NULL);
        // execlp("/bin/ls", argv[1], NULL);
        // execvp(argv[1], NULL);
        sleep(1);
        printf("%s\n", *(argv+1));
        execvp(argv[1], &argv[1]);
        exit(0);
    } else {
        wait(NULL);
        printf("parent_process\n");
        
        struct timeval end_time;

        gettimeofday(&end_time,NULL);

        double elapsed_time = (end_time.tv_sec - start_time->tv_sec) + (end_time.tv_usec - start_time->tv_usec) / 1000000;

        printf("elapsed_time : %fs\n", elapsed_time);
        exit(0);
            
    }

    shm_unlink(name);
    return 0;
}