#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>

/* 실행 결과
    pid - 0 , 1734 , parent - 20558  - 5
    pid - 0 , 1735 , parent - 1734  - 16
    pid - 0 , 1736 , parent - 1735  - 8
    pid - 0 , 1737 , parent - 1736  - 4
    pid - 0 , 1738 , parent - 1737  - 2
    pid - 0 , 1739 , parent - 1738  - 1
*/

int main(int argc, char *argv[])
{
    pid_t pid = 0;

    int start_number = strtol(argv[1],NULL,10);
    
    while(pid==0){
        printf("pid - %d , %d , parent - %d  - ", pid, getpid(), getppid());
        
        if (start_number == 1) {
            printf("1");
            return 0;
        };
        printf("%d\n",start_number);
        fflush(stdout); // while 시작이나 끝에 pritnf 를 하지않으면 flush 를 해주지 않으면 제대로 동작하지 않았음
        if (start_number%2 == 0) {
            start_number /= 2;
        }else {
            start_number = start_number * 3 + 1;
        }
        pid = fork();
        // printf("B");
    }
    wait(NULL);
    return 0;
}