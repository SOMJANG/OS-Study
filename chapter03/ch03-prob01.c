#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // unix 계열에서 동작하는 c 컴파일러에 존재하는 헤더 파일

int main() {
    pid_t pid; // pid_t 는 2 ~ 32768 사이 범위의 값을 저장할 수 있음  // -1 도 가능

    pid = fork(); // fork 함수 실행 - 실패 시 -1 return // 자식프로세스 생성

    // fork 를 실행하면 부모 프로세스와 자식 프로세스에서 두번 씩 반환
    printf("pid - %d / getpid - %d /  getppid - %d\n", pid, getpid(), getppid()); 

    // 그래서 위 print 문을 추가하여 실행해보면 
    // pid - 10377 / getpid - 10376 /  getppid - 5319
    // pid - 0 / getpid - 10377 /  getppid - 10376
    // 위와 같이 2번 출력됨
    // pid 가 0일 경우에는 자식 프로세스 / 0보다 클때는 부모 프로세스 / -1 일떄는 프로세스 생성 실패!
    // 따라서 이 각각 두번 반환 동안 어떤 동작을 할 것인지 if 또는 switch 문으로 분기를 시켜주어야 함

    // 우리가 원하는 것은 좀비 프로세스 생성!
    // 먼저 좀비 프로세스가 무엇인가 
    // ㄴ 자식 프로세스가 먼저 종료되었지만
    // ㄴ 부모 프로세스가 종료된 자식을 완벽하게 회수를 하지 못하고 계속 남아있는 상태
    // ps -l 명령어를 입력했을떄 S column 에 Z 로 표시되는 프로세스

    // 그대로 아래에 코드로 구현해보면
    
    // pid 가 0보다 큰 값이어서 부모 프로세스 인 경우
    if (pid > 0) {
    	printf("Parent Process - %d\n", getpid());
    	sleep(10); // 10초 동안 sleep
    	exit(0);
    } else if (pid == 0) { // 자식 프로세스인 경우
    	printf("Child Process - %d\n", getpid());
    	exit(0); // 바로 종료
    } else {
    	printf("fork() Error\n");
    	exit(1); // 	exit(1); // exit(1) 은 Fail 케이스일 경우 / 성공 시 exit(0)
    }

    // 코드를 실행한 뒤에 ps -l 을 실행해보면 아래와 같이 Z+ 로 생성
    // (base) somjang@DongHyunui-MacBookPro ~ % ps -l
    // UID   PID  PPID        F CPU PRI NI       SZ    RSS WCHAN   S             ADDR TTY           TIME CMD
    // 501  5319  5318     4006   0  31  0 409086416   7440 -      S                   0 ttys000    0:00.51 -zsh
    // 501 10576  5319     4006   0  31  0 408503920   1104 -      S+                  0 ttys000    0:00.01 ./pro01
    // 501 10577 10576     2006   0   0  0        0      0 -       Z+                  0 ttys000    0:00.00 <defunct>
    // 501  5635  5634     4006   0  31  0 408842592   5216 -      S                   0 ttys001    0:00.37 -zsh
}
