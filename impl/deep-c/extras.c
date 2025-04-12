#include <stdio.h>
#include <stdarg.h>

enum shape {
    sphere = 10,
    cube = 11,
    cuboid = 12
};

struct employee {
    char name[20];
    int age;
    enum shape fav_shape;
};

typedef struct employee EMP;

void extra1() {
    enum shape s1, s2;

    s1 = sphere;

    printf("s1 = %d\n", s1);

    s1 = 12;

    if (s1 == sphere) {
        printf("s1 is sphere\n");
    } else {
        printf("s1 is cuboid\n");
    }
}

void extra2() {
    EMP e1 = {
        "Boss", 50, sphere
    };

    printf("e1: %s, %d, %d\n", e1.name, e1.age, e1.fav_shape);
}

void display() {
    printf("printf random stuff\n");
}

void extra3() {
    printf("address of display(): %u\n", display);

    void (*func_ptr)();
    func_ptr = display;

    (*func_ptr)();
}

int get_max(int totnum, ...) {
    
    va_list ptr;
    va_start(ptr, totnum);
    
    int max_num, num;
    max_num = va_arg(ptr, int);

    for (int i = 1; i < totnum; i++) {
        int num = va_arg(ptr, int);
        if (num > max_num) {
            max_num = num;
        }
    }

    return max_num;
}

void extra4() {
    printf("Max 1: %d\n", get_max(3, 5, 10, 2));
    printf("Max 1: %d\n", get_max(6, 5, 10, 2, 89, 43, 99));
}

static volatile int counter = 0;

void extra5() {
    while (1) {
        int d;
        scanf("%d", &d);

        switch (d) {
            case 0:
                return;
            case 1:
                counter += 1;
                printf("counter = %d\n", counter);
                break;
            case 2:
                counter += 2;
                printf("counter = %d\n", counter);
                break;
            default:
                printf("counter = %d\n", counter);
                break;
        }
    }
}

int main(int argc, char *argv[]) {

    for (int i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // extra1();
    // extra2();
    // extra3();
    // extra4();
    extra5();

    return 0;
}