#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>


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

void file6() {
    struct employee {
        char name[20];
        int age;
        double salary;
    };

    struct employee emps[] = {
        {
            "Jake", 25, 1000.00
        },
        {
            "Alice", 30, 4000.50
        },
        {
            "Hugh", 27, 3000.00
        },
        {
            "Tim", 45, 10000.75
        }
    };

    FILE* fp = fopen("emp.csv", "w");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    // fprintf(fp, "name,age,salary\n");
    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%s %d %F\n", emps[i].name, emps[i].age, emps[i].salary);
    }

    fclose(fp);
    printf("Write to CSV complete.\n");
}

void file7() {
    struct employee {
        char name[20];
        int age;
        double salary;
    };

    FILE* fp = fopen("emp.csv", "r");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    struct employee* emps[20];
    int i = 0;
    int n_rows = 0;
    while (i < 20) {
        struct employee *emp_row = (struct employee *) malloc(sizeof(struct employee));
        int x = fscanf(fp, "%s %d %lF", emp_row -> name, &emp_row -> age, &emp_row -> salary);

        if (x == EOF) {
            break;
        }

        emps[i] = emp_row;
        i++;
        n_rows++;
    }

    for (int i = 0; i < n_rows; i++) {
        printf("%d,%s,%d,%lF\n", i + 1, emps[i] -> name, emps[i] -> age, emps[i] -> salary);
    }

    fclose(fp);

    printf("Read %d rows\n", n_rows);
}

void file8() {
    struct employee {
        char name[20];
        int age;
        double salary;
    };

    FILE* fp = fopen("emp_2.csv", "wb");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    struct employee emps[] = {
        {
            "Jake", 25, 1000.00
        },
        {
            "Alice", 30, 4000.50
        },
        {
            "Hugh", 27, 3000.00
        },
        {
            "Tim", 45, 10000.75
        }
    };

    for (int i = 0; i < 4; i++) {
        fwrite(&emps[i], sizeof(emps[i]), 1, fp);
    }

    fclose(fp);
    printf("Write to CSV complete.\n");
}

void file9() {
    struct employee {
        char name[20];
        int age;
        double salary;
    };

    FILE* fp = fopen("emp_2.csv", "rb");

    if (fp == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }

    struct employee emp;

    while(fread(&emp, sizeof(emp), 1, fp) == 1) {
        printf("%s, %d, %lF\n", emp.name, emp.age, emp.salary);
    }

    fclose(fp);
    printf("Read from CSV complete.\n");
}

void file10() {
    int infile, outfile, bytes;
    infile = open("fun1.c", O_RDONLY);
    outfile = open("fun1_copy.c", O_CREAT | O_WRONLY, 0644);

    if (infile == -1 || outfile == -1) {
        printf("Cannot open files.\n");
        exit(1);
    }

    int BF_SIZE = 512;
    char buffer[BF_SIZE];

    int tot_bytes = 0;
    while (1) {
        bytes = read(infile, buffer, BF_SIZE);

        if (bytes == 0) {
            break;
        }

        write(outfile, buffer, bytes);
        tot_bytes += bytes;
    }

    printf("I: %d bytes copied.\n", tot_bytes);

    close(infile);
    close(outfile);
}



int main() {
    // file1();
    // file2();
    // file3();
    // file4();
    // file5();
    // file6();
    // file7();
    // file8();
    // file9();
    file10();
    return 0;
}

