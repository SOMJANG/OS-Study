#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80 /* The maximum length command */

int main(void) {
    char *args[MAX_LINE/2 + 1];
    char command[MAX_LINE];
    
    int should_run = 1;
    int command_pointer = 0;
    int has_amp = 0;
    int status;

    while (should_run) {
        printf("osh> ");
        fflush(stdout);

        fgets(command, MAX_LINE, stdin);

        if (command[strlen(command) - 1] == '\n') {
            command[strlen(command) - 1] = '\0';
        }

        printf("%s\n", command);

        if (strcmp(command, "exit") == 0){
            should_run = 0;
            exit(0);
            break;
        } else {
            pid_t pid;

            printf("command - %s\n", command);

            char *ptr = strtok(command, " ");
        
            while (ptr != NULL) {
                args[command_pointer] = malloc(strlen(ptr) + 1);
                strcpy(args[command_pointer++], ptr);
                ptr = strtok(NULL, " ");
            }

            if (strcmp(args[command_pointer-1], "&") == 0) {
                args[command_pointer-1] = NULL;
                has_amp = 1;
            } // & 대신 NULL 을 넣어야하나?

            if (pid > 0) {
                printf("Parent Process - %d\n", getpid());
                if (has_amp == 1) {
                    waitpid(pid, &status, 0);
                }
                wait(NULL);
                exit(0);
            } else if (pid == 0) { // 자식 프로세스인 경우
                printf("Child Process - %d\n", getpid());

                execvp(args[0], args);

                for (int i = 0; i < command_pointer; i++) {
                    free(args[i]);
                }
                exit(0); // 바로 종료
            } else {
                printf("fork() Error\n");
                exit(1); // 	exit(1); // exit(1) 은 Fail 케이스일 경우 / 성공 시 exit(0)
            }
        }

        command_pointer++;
    }

    

    return 0;
}
