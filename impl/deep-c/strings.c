#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PNL printf("\n")
#define PSL printf("---\n")

void print_str(char *s) {
    char *x = s;
    while (*x != '\0') {
        printf("%c", *x);
        x++;
    }
    PNL;
}

void str1() {
    char str[] = "hello";
    print_str(str);
}

void str2() {
    char str[] = {'a', 'b', 'c'};
    print_str(str);
    printf("%s\n", str);
}

void str3() {
    char name[25];
    gets(name);
    puts("Hello ");
    puts(name);
}

void str4() {
    char str[] = "Yelp"; // automatically gets a '\0' at the end
    char *p = "Mello"; // C compiler has stored it somewhere. We know a pointer to it.
    printf("%s\n", str);
    printf("%s\n", p);

    p = str;
    printf("%s\n", p);
    printf("%c\n", *(str + 1));
    printf("%c\n", *(p));
    printf("%c\n", *(p + 1));

    // *str = "ghibli";     // str is const, immutable. "Yelp" is variable.
    // printf("%s\n", str);
    print_str(str);
    PSL;
    p = "Jim";
    *p = 'K'; // p is variable. but "Jim" is a const, immutable.
    printf("%s\n", p);
}

void str5() {
    char src[20] = "Bimbo Jok";
    char target[20] = "Fupu Wou";

    printf("%d\n", strcmp(target, src));

    strcat(target, src);
    printf("%s\n", target);

    char *src1;
    printf("Before: %s\n", src1);
    src1 = strdup(src);
    printf("After: %s\n", src1);

    printf("Before: %s\n", target);
    strcpy(target, src);
    printf("After: %s\n", target);


    int l1 = strlen(src);
    printf("before (len = %d): %s\n", l1, src);
    src[5] = '\0';
    int l2 = strlen(src);
    printf("after (len = %d): %s\n", l2, src);
    printf("%c %c %c\n", src[6], src[7], src[8]);

}

void str6() {
    char strs[][10] = {
        "alice",
        "bob",
        "cory",
        "donald"
    };

    // strs[1][0] = 'R';

    char input[20];
    printf("Enter name: ");
    scanf("%s", input);

    for (int i = 0; i < 4; i++) {
        if (!strcmp(strs[i], input)) {
            printf("Found\n");
        }
        // printf("%s\n", strs[i]);
    }
}

void str7() {
    char* p[] = {
        "alice",
        "bob",
        "cory",
        "donald"
    };

    char input[20];
    printf("Enter name: ");
    scanf("%s", input);

    for (int i = 0; i < 4; i++) {
        if (!strcmp(p[i], input)) {
            printf("Found\n");
        }
        // printf("%s\n", strs[i]);
    }
}

void str8() {
    char *db[5];
    char input[50];
    printf("Enter 5 names\n");
    for (int i = 0; i < 5; i++) {
        scanf("%s", input);
        int len = strlen(input);
        char *p = (char *) malloc(len + 1);
        strcpy(p, input);
        db[i] = p;
    }
    for (int i = 0; i < 5; i++) {
        printf("Name %d: %s\n", i + 1, db[i]);
    }
}

int main() {
    // str1();
    // str2();
    // str3();
    // str4();
    // str5();
    // str6();
    // str7();
    str8();
    return 0;
}