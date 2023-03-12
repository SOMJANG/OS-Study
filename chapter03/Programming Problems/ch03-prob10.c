#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>


// pipe
// Parent          Child
// fd[0] <- pipe -- fd[1]
// fd[1] -- pipe -> fd[0]

// READ_END 0 / WRITE_END 1
// Parent R END -> W END
// Child  W END -> R END


struct copyinfo {
    char filename[100];
    char destination[100];
};


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
        // close(fd[1]);

        printf("child process\n");
        struct copyinfo copydata;

        read(fd[0], &copydata, sizeof(copydata) + 1);

        // printf("%s / %s\n", copydata.filename, copydata.destination);

        FILE* originfile;
        FILE* copyfile;

        char txtline[1024];
        char *line;
        char *copylines = "";

        originfile = fopen(copydata.filename, "r");
        copyfile = fopen(copydata.destination, "w");

        rewind(copyfile);

        while (feof(originfile) == 0) {
            line = fgets(txtline, 1024, originfile);
            fputs(line, copyfile);
        }

        fclose(originfile);
        fclose(copyfile);


        // close(fd[0]);
        exit(0);
    } else {
        close(fd[0]);

        printf("parent process\n");
        struct copyinfo copydata;

        // printf("%s\n", argv[0]);
        // printf("%s\n", argv[1]);
        // printf("%s\n", argv[2]);

        strcpy(copydata.filename, argv[1]);
        strcpy(copydata.destination, argv[2]);

        write(fd[1], &copydata, sizeof(copydata) + 1);

        close(fd[1]);
        exit(0);
    }

    return 0;
}