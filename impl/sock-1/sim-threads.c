#include<stdio.h>
#include<assert.h>
#include<pthread.h>

static volatile int counter = 0;

void *mythread(void *arg) {
    printf("%s\n", (char *) arg);
    return NULL;
}


void *add(void *arg) {
    int i = 0;
    for (i = 0; i < 10000; i++) {
        counter += 1;
    }
}

int main() {
    pthread_t p1, p2;
    printf("main: begin. counter = %d\n", counter);
    int rc;
    rc = pthread_create(&p1, NULL, add, "A"); assert(rc == 0);
    rc = pthread_create(&p2, NULL, add, "B"); assert(rc == 0);

    rc = pthread_join(p1, NULL); assert(rc == 0);
    rc = pthread_join(p2, NULL); assert(rc == 0);

    printf("main: end. counter  %d\n", counter);
    return 0;
}