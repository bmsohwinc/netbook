#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void struct1() {
    struct book {
        int pages;
        char name;
        float price;
    };

    struct book b1, b2;
    char x;
    // printf("Enter b1 details: ");
    // scanf("%c %f %d", &b1.name, &b1.price, &b1.pages);
    // scanf("%c", &x);
    // printf("Enter b2 details: ");
    // scanf("%c %f %d", &b2.name, &b2.price, &b2.pages);
    

    // printf("Your book details:\n");
    // printf("B1: %c, %f, %d\n", b1.name, b1.price, b1.pages);
    // printf("B1: %c, %f, %d\n", b2.name, b2.price, b2.pages);

    printf("B1 addresses: %u, %u, %u\n", &b1.name, &b1.price, &b1.pages);
}

void struct2() {
    struct book {
        char* name;
        int pages;
    };

    struct book db[] = {
        {"Harry", 200},
        {"Lord", 500}
    };

    for (int i = 0; i < 2; i++) {
        printf("%s, %d\n", db[i].name, db[i].pages);
    }
}

void struct3() {

    struct author {
        char* name;
    };
    struct book {
        char* name;
        int pages;
        struct author a;
    };

    struct book b1 = {"Art of War", 200, "Sun Tzu"};
    struct book b2;
    b2 = b1;

    printf("%s %d %s\n", b2.name, b2.pages, b2.a.name);
    
}

struct car {
    char* name;
    int id;
};

void display(struct car car) {
    printf("Car name = %s, Car id = %d\n", car.name, car.id);
}

void display_ptr(struct car* car) {
    printf("Car name = %s, Car id = %d\n", car -> name, car -> id);
}

void struct4() {
    struct car my_car = {"Maruti Alto", 235};
    display(my_car);
    display_ptr(&my_car);
}

int main() {
    // struct1();
    // struct2();
    // struct3();
    struct4();
    return 0;
}
