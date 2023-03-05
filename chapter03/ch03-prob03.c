#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdlib.h>


#define MIN_PID 300
#define MAX_PID 5000

int pid_map[(MAX_PID - MIN_PID + 1)];

int allocate_map(void) {
    for (int i = 0; i < (MAX_PID - MIN_PID + 1); i++) {
        pid_map[i] = 0;
    }

    if (pid_map[(MAX_PID - MIN_PID)] == 0) {
        return 1;
    } else {
        return -1;
    }
}

int allocate_pid(void) {
    int new_pid = -1;

    for (int i = 0; i < (MAX_PID - MIN_PID + 1); i++) {
        if (pid_map[i] == 0) {
            new_pid = i + MIN_PID;
            pid_map[i] = 1;
            break;
        }
    }

    return new_pid;
}

void release_pid(int pid) {
    if (0 <= pid && pid < MAX_PID - MIN_PID + 1) {
        pid_map[pid - MIN_PID] = 0;
    }
}

int main(int args, char *argv[]) {
    allocate_map();

    int new_pid = allocate_pid();

    printf("first new pid - %d\n", new_pid);

    int new_pid2 = allocate_pid();

    printf("second new pid - %d\n", new_pid2);

    int new_pid3 = allocate_pid();

    printf("third new pid - %d\n", new_pid3);


    release_pid(new_pid2);

    for (int i=0; i < (MAX_PID - MIN_PID + 1); i++) {
        int pid = allocate_pid();

        if (pid == -1) {
            printf("fail pid = %d\n", pid);
        }
    }
    return 0;
}