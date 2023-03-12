#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {
    pid_t pid;
    
    // 명령어에 시작 숫자가 입력되지 않았다면 입력 해달라는 메세지 출력 후 종료
    if (argc == 1) {
        printf("Please input start number after exec command\n");
        return 0;
    }

    pid = fork();

    // atoi 함수를 활용하여 입력 받은 숫자를 문자에서 int 형으로 바꾸어줌
    int number = atoi(argv[1]);

    if (pid < 0) {
        printf("fork() Error\n");
        exit(1);
    } else if (pid == 0) {
        printf("%d, ", number);
        // Colatz 추측 실행 부분
        // number 가 짝수이면 number = number / 2
        // number 가 홀수이면 number = 3 * number + 1
        while (number != 1) {
            if (number % 2 == 0) {
                number /= 2;
            } else {
                number = 3 * number + 1;
            }
            if (number != 1) {
                printf("%d, ", number);
            } else {
                printf("%d\n", number);
            }   
        }
        exit(0);
    } else {
        // child process 가 끝날때 까지 대기
        wait(NULL);
        exit(0);
    }

    return 0;
}