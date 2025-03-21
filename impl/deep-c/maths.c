#include <stdio.h>
#include <math.h>
#include "fun1.c"

int counter = 0;

void increase();
void decrease();

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

    int a = 2;
    int b = 3;
    printf("Before: a = %d, b = %d\n", a, b);
    sum(&a, &b);
    printf("After: a = %d, b = %d\n", a, b);

    unsigned a1 = 1;
    unsigned a2 = a1 - 2u;
    printf("a1 = %d\n", a1);
    printf("a2 = %d\n", a2);
    printf("a2 = %u\n", a2);

    static_incr();
    static_incr();

    print_separator();

    increase();
    increase();
    printf("counter = %d\n", counter);
    decrease();
    printf("counter = %d\n", counter);

    return 0;
}