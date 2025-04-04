#include <stdio.h>
#include <math.h>
#include "fun1.c"

#include "myfile.h"
#include "myfile1.h"

#define AND &&
#define OR ||

#define IN_RANGE(a) (a > 0 AND a < 100)

#define LOG_METRIC

#define WINDOWS 0
#define MAC_OS 1
#define LINUX 2

#define MACHINE 2

int counter = 0;

void increase();
void decrease();

void send_packet() {
    counter++;

    #ifndef LOG_METRIC
        printf("Packet sent at 11 pm GMT\n");
    #endif
}

void sum(int *a, int *b) {
    *a = 20;
    // printf("a = %d, b = %d, a + b = %d\n", *a, *b, *a + *b);
    // printf("&a = %u, &b = %u\n", a, b);
}

void static_incr() {
    static int i = 1;
    printf("Before: i = %d\n", i);
    i++;
    printf("After: i = %d\n", i);

}

void run_extern_counter() {
    int done = 0;
    while (!done) {
        int u_resp = 1;
        scanf("%d", &u_resp);
        switch (u_resp)
        {
            case 1:
                increase();
                break;
            case 2:
                decrease();
                break;
            case 3:
                done = 1;
                break;
            default:
                break;
        }

        printf(">> counter = %d\n", counter);
    }
}


void run_macro_1() {
    if (2 < 3 AND 3 < 5) {
        printf("Zero\n");
    } else {
        printf("Jero\n");
    }

    int a = 10;
    if (IN_RANGE(10)) {
        printf("In range\n");
    }

    if (!IN_RANGE(100)) {
        printf("Not in range\n");
    }
}

void show_startup_screen() {
    #if MACHINE == WINDOWS
        printf("Windows emulator says: Hello\n");
    #elif MACHINE == MAC_OS
        printf("Mac OS emulator says: Mello\n");
    #elif MACHINE == LINUX
        printf("Linux emulator says: Lello\n");
    #else
        printf("No emulator said anything\n");
    #endif
}

void print_separator() {
    printf("-----------------------\n");
}

int main() {
    // int x = 2;
    // float y = 3.0;

    // y = x;
    // x = y;

    // printf("%f\n", pow(3.0, 2.0));
    // printf("x = %d,  y = %f\n", x, y);

    // int a = 2;
    // int b = 3;
    // printf("Before: a = %d, b = %d\n", a, b);
    // sum(&a, &b);
    // printf("After: a = %d, b = %d\n", a, b);

    // unsigned a1 = 1;
    // unsigned a2 = a1 - 2u;
    // printf("a1 = %d\n", a1);
    // printf("a2 = %d\n", a2);
    // printf("a2 = %u\n", a2);

    // static_incr();
    // static_incr();

    // print_separator();

    // increase();
    // increase();
    // printf("counter = %d\n", counter);
    // decrease();
    // printf("counter = %d\n", counter);

    // run_extern_counter();

    // run_macro_1();

    // send_packet();

    // run1();

    show_startup_screen();

    return 0;
}