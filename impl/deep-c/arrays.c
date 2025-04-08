#include <stdio.h>

#define PNL printf("\n")

void display(int *n);
void show(int **n);

void arr1() {
    int marks[5];
    for (int i = 0; i < 5; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &marks[i]);
    }

    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += marks[i];
    }

    double avg = (sum * 1.0) / 5.0;

    printf("Sum = %d, Avg = %F\n", sum, avg);
}

void arr2() {
    int marks[5] = {1, 2, 3};

    printf("Sum = %d\n", marks[0] + marks[1] + marks[2] + marks[3]);
    printf("marks[3] = %d, marks[5] = %d\n", marks[3], marks[5]);
}

void arr3() {
    int marks[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) {
        display(&marks[i]);
    }
}

void display(int *n) {
    show(&n);
}

void show(int **n) {
    printf("OOf! Finally printing: %d\n", **n);
}

void arr4() {
    int marks[4] = {20, 50, 40, 30};
    for (int i = 0; i < 4; i++) {
        printf("element #%d = %d at loc = %u\n", i + 1, marks[i], &marks[i]);
    }
    printf("---\n");
    int *x = &marks[1];
    printf("*x = %d, * x - 1 = %d, * x + 1 = %d\n", *x, *(x - 1), *(x + 1));
    printf("---\n");
}

void display_arr(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%2d ", arr[i]);
    }
    printf("\n");
}

void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int *x = arr + i;
            int *y = arr + j;

            if (*x > *y) {
                int t = *x;
                *x = *y;
                *y = t;
            }
        }
    }
}

void arr5() {
    int n = 5;
    int marks[] = {50, 20, 30, 15, 40};
    printf("Before sorting: ");
    display_arr(marks, n);
    bubble_sort(marks, n);
    printf("After sorting: ");
    display_arr(marks, n);
}

void arr6() {
    int data[][2] = {
        {1, 0},
        {0, 1}
    };

    display_arr(data[0], 2);
    display_arr(data[1], 2);
}

void arr7() {
    int data[][3] = {
        {3, 4, 5},
        {1, 2, 1},
        {6, 8, 6}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", *(*(data + j) + i));
        }
        printf("\n");
    }
}

void printer1(int (*a)[4], int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", *(*(a + i) + j));
        }
        printf("\n");
    }
}

void printer2(int *a, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", *(a + (i * m) + j));
            // printf("%d ", *(*(a + i) + j)); // is wrong. but why?
        }
        printf("\n");
    }
}

void arr8() {
    int data[][4] = {
        {3, 4, 5, 7},
        {1, 2, 1, 7},
        {6, 8, 6, 7}
    };

    printer1(data, 3, 4);
    printer2(data, 3, 4);

}

void arr9() {
    int x = 3;
    int y = 4;
    int z = 5;
    int *data1[] = {&x, &y, &z};
    for (int i = 0; i < 3; i++) {
        printf("%d ", *(data1[i]));
    }
    PNL;
}


int main() {
    // arr1();
    // arr2();
    // arr3();
    // arr4();
    // arr5();
    // arr6();
    // arr7();
    // arr8();
    arr9();
    return 0;
}