#include <stdio.h>
#include <signal.h>
#include <bits/types/sigset_t.h>
#include <bits/sigaction.h>

void sighandler(int signum) {
    printf("SIGINT received. Inside sighandler!\n");
}

void sig1() {
    while (1) {
        printf("hello!\n");
    }
}

void sig2() {
    char buffer[80] = "\0";

    sigset_t sigmask;

    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGINT);
    sigaddset(&sigmask, SIGTERM);

    sigprocmask(SIG_BLOCK, &sigmask, NULL);
    while (1)
    {
        printf("Enter number: ");
        int d;
        scanf("%d", &d);
        if (d == 0) {
            break;
        }
        printf("You entered: %d\n", d);
    }
    
    sigprocmask(SIG_UNBLOCK, &sigmask, NULL);

    while (1) {
        printf("hello\n");
    }
    
    
}

int main() {

    signal(SIGINT, sighandler);
    
    // sig1();
    sig2();

    return 0;
}