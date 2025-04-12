#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file1() {
    FILE *fp;

    char ch;

    fp = fopen("fun1.c", "r");

    if (fp == NULL) {
        printf("[ E ] File cannot be opened.\n");
        exit(1);
    }

    while (1) {
        ch = fgetc(fp);
        if (ch == EOF) {
            break;
        }

        printf("%c", ch);
    }

    printf("\n");
    fclose(fp);
}

void file2() {
    FILE *fp = fopen("fun1.c", "r");
    char x;
    int no_spaces = 0;
    int no_newlines = 0;
    int no_chars = 0;
    while ((x = fgetc(fp)) != EOF) {
        no_chars++;
        if (x == ' ') {
            no_spaces++;
        }

        if (x == '\n') {
            no_newlines++;
        }
    }

    fclose(fp);

    printf("Chars = %d, Spaces = %d, Newlines = %d\n", no_chars, no_spaces, no_newlines);
}

void file3() {
    FILE *fp_src = fopen("fun1.c", "r");
    FILE *fp_tgt = fopen("fun1_copy.c", "w");

    if (fp_src == NULL || fp_tgt == NULL) {
        printf("ERROR: Unable to open files.\n");
        exit(1);
    }

    char x;
    int count = 0;

    while (1) {
        x = fgetc(fp_src);

        if (x == EOF) {
            break;
        }

        fputc(x, fp_tgt);
        count++;
    }  

    fclose(fp_src);
    fclose(fp_tgt);

    printf("%d characters written.\n", count);
}

void file4() {
    FILE* fp_tgt = fopen("poem.txt", "w");
    if (fp_tgt == NULL) {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }

    char input[50];

    printf("Enter lines of a poem:\n");
    while (1) {
        gets(input);
        if (strlen(input) == 0) {
            break;
        }

        fputs(input, fp_tgt);
        fputs("\n", fp_tgt);
    }

    fclose(fp_tgt);
}

void file5() {
    FILE* fp_src = fopen("poem.txt", "r");

    if (fp_src == NULL) {
        printf("ERROR: Cannot open file.\n");
        exit(1);
    }

    char input[50];
    while (fgets(input, 49, fp_src) != NULL) {
        printf("%s\n", input);
    }
    printf("\n");
    
    fclose(fp_src);
}

int main() {
    // file1();
    // file2();
    // file3();
    // file4();
    file5();
    return 0;
}

