#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

// 콜라츠 추측의 최대 loop 회수가 5,764,607,523,034,234,880 을 넣었을때 880회 라고 하여
// 그보다 조금 더 큰 1024로 SIZE 를 설정
#define SIZE 1024

int main(int argc, char *argv[]) {
    pid_t pid;
    
    // 명령어에 시작 숫자가 입력되지 않았다면 입력 해달라는 메세지 출력 후 종료
    if (argc == 1) {
        printf("Please input start number after exec command\n");
        return 0;
    }

    int fd;
    
    char *name = "collatz";

    fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(fd, SIZE);

    int *collatz_numbers;

    collatz_numbers = (int *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    int loop_num = 0;

    pid = fork();

    // atoi 함수를 활용하여 입력 받은 숫자를 문자에서 int 형으로 바꾸어줌
    int number = atoi(argv[1]);

    if (pid < 0) {
        printf("fork() Error\n");
        exit(1);
    } else if (pid == 0) {
        collatz_numbers[loop_num++] = number;
        
        // Colatz 추측 실행 부분
        // number 가 짝수이면 number = number / 2
        // number 가 홀수이면 number = 3 * number + 1
        while (number != 1) {
            if (number % 2 == 0) {
                number /= 2;
            } else {
                number = 3 * number + 1;
            }
            
            collatz_numbers[loop_num++] = number;
        }
        exit(0);
    } else {
        // child process 가 끝날때 까지 대기
        wait(NULL);

        int print_num = 0;

        while (collatz_numbers[print_num] != 0) {
            if (collatz_numbers[print_num] != 1) {
                printf("%d, ", collatz_numbers[print_num++]);
            } else {
                printf("%d\n", collatz_numbers[print_num++]);
            }
        }

        exit(0);
        
    }

    shm_unlink(name);

    return 0;
}