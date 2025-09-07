#include <sys/types.h>
#include<stdio.h>
#include <unistd.h> 
#include<sys/wait.h>
#include<string.h>

#define MAX_CMD_LEN 50
#define MAX_ARG_LEN 5
#define PORT 8080

int main() {
    printf("Hello before forking!\n");

    while (1) {
        printf("srsh$ ");
        char cmd_input[MAX_CMD_LEN];
        fgets(cmd_input, MAX_CMD_LEN, stdin);

        // printf("Your input: %s\n", cmd_input);
        printf("-- Started executing user command --\n");

        int pid = fork();
        
        if (pid == 0) {
            // printf("Child speaks... I am %d. My parent is: %d\n", getpid(), getppid());

            char *myargs[MAX_ARG_LEN];

            char *token = strtok(cmd_input, " ");
            int arg_idx = 0;
            while (token != NULL && (arg_idx < MAX_ARG_LEN - 1)) {
                size_t len = strlen(token);
                if (len > 0 && token[len - 1] == '\n') {
                    token[len - 1] = '\0';
                }
                // printf("Token: %s. strdup: %s\n", token, strdup(token));
                myargs[arg_idx] = strdup(token);
                token = strtok(NULL, " ");
                arg_idx++;
            }
            myargs[arg_idx] = NULL;
            
            // myargs[0] = strdup("wc");
            // myargs[1] = strdup("client.c");
            // myargs[2] = NULL;
            
            execvp(myargs[0], myargs);
        } else if (pid > 0) {
            int wc = wait(NULL);
            printf("-- Finished executing user command --\n\n");
            // printf("Parent speaks: I am %d. My parent is: %d. My child is: %d (wc: %d)\n", getpid(), getppid(), pid, wc);
        }
    
    }
    printf("Hello after forking...\n");
    return 0;
}
