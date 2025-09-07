/*

Ref: https://cse.iitkgp.ac.in/~abhij/course/lab/OSL/shm.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>


void handle_child(int shm_id) {
    /*
        - Attach to shm
        - Inside infinite loop
            - if shm's value is different
                - print the value
                - update previous value
            - sleep for 500 ms
        - Detach from shm
    */
    int *b;
    int prev_value = -1;
    struct timespec ts;

    ts.tv_sec = 0;
    ts.tv_nsec = 200000000L; /* 200 ms = 200,000,000 ns*/

    b = (int *) shmat(shm_id, 0, 0);

    for ( ;; ) {
        if (prev_value != b[0]) {
            printf("[ I ]: Child: Detected change: prev_value = %d. New value = %d\n", prev_value, b[0]);
            prev_value = b[0];
        }
        nanosleep(&ts, NULL);
    }

    shmdt(b);
}


void handle_parent(int shm_id) {
    /*
        - Attach to shm
        - Inside infinite loop
            - Get user input
            - Write it to shm
        - Detach from shm
    */
    int *a;
    int user_number;

    a = (int *) shmat(shm_id, 0, 0);

    for ( ;; ) {
        printf("[ I ] Parent: Enter a number (0-999). Enter -1 to exit: ");
        scanf("%d", &user_number);

        if (user_number == -1) {
            break;
        }

        a[0] = user_number;
    }

    shmdt(a);
}


int main() {

    int shm_id, status;
    int *a, *b;
    int i;
    __pid_t child_pid;

    shm_id = shmget(IPC_PRIVATE, sizeof(int), 0777 | IPC_CREAT); 
    
    child_pid = fork();

    if (child_pid < 0) {
        printf("ERR: Could not fork. Exiting.\n");
        shmctl(shm_id, IPC_RMID, 0);
        exit(1);
    }

    if (child_pid == 0) {
        handle_child(shm_id);
    } else {
        handle_parent(shm_id);
        shmctl(shm_id, IPC_RMID, 0);
    }

    return 0;
}

