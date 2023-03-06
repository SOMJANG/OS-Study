#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    int fd1[2], fd2[2];

    pid_t pid;

    pipe(fd1); // pipe_1
    pipe(fd2); // pipe_2

    if (pipe < 0) {
        printf("Fail to Create pipe\n");
    }

    pid = fork();

    if (pid < 0) {
        printf("fork() Error\n");
        exit(1);
    } else if (pid == 0) {
        close(fd1[1]); // close WRITE_END of pipe_1
        close(fd2[0]); // close READ_END of pipe_2

        char recive_message[1024], modified_message[1024];
        
        read(fd1[0], recive_message, sizeof(recive_message) + 1);

        printf("recieve message : %s\n", recive_message);

        for (int i = 0; i < strlen(recive_message) + 1; i++) {
            // 대문자이면 소문자로 변환 (tolower) ( A = 65 / Z = 90)
            // 소문자이면 대문자로 변환 (toupper) ( a = 97 / z = 122)
            // 공백, 특수문자, 숫자 등은 그대로
            if (65 <= recive_message[i] && recive_message[i] <= 90) {
                modified_message[i] = tolower(recive_message[i]);
            } else if (97 <= recive_message[i] && recive_message[i] <= 122) {
                modified_message[i] = toupper(recive_message[i]);
            } else {
                modified_message[i] = recive_message[i];
            }
            
        }

        write(fd2[1], modified_message, strlen(modified_message) + 1);
        sleep(1);

        execvp(argv[1], &argv[1]);
        
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    } else {
        close(fd1[0]); // close READ_END of pipe_1
        close(fd2[1]); // close WRITE_END of pipe_2

        char send_message[1024], modified_message[1024];

        printf("Please input String : ");
        // scanf("%s", send_message); <- 띄어쓰기를 포함해서 입력 받지 못함
        // 정규식처럼 적어주면 가능하지만 띄어쓰기를 포함해서 입력 받을 수 있는 fgets 사용
        fgets(send_message, sizeof(send_message), stdin);

        printf("send message : %s\n", send_message);

        write(fd1[1], send_message, sizeof(send_message) + 1);
        wait(NULL);
        read(fd2[0], modified_message, sizeof(modified_message) + 1);
        
        printf("modified message : %s\n", modified_message);

        close(fd1[1]); 
        close(fd2[0]);
        exit(0);
    }

    return 0;
}