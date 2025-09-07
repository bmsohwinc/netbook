// Server side C program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <asm-generic/socket.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 20
#define MAX_MSG_LEN 200
#define PORT 8080

int main(int argc, char const* argv[])
{
    int sfd1, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = { 0 };
    char* hello = "Hello from server";

    // Creating socket file descriptor
    if ((sfd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(sfd1, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(sfd1, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(sfd1, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }


    int client_idx = 0;

    int clients[MAX_CLIENTS] = { 0 };

    while (client_idx < MAX_CLIENTS) {
        if ((new_socket
            = accept(sfd1, (struct sockaddr*)&address,
                    &addrlen))
            < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        clients[client_idx] = new_socket;
        client_idx++;

        int pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {

            printf("Child speaks... I am %d. My parent is: %d\n", getpid(), getppid());

            // welcome message
            send(new_socket, hello, strlen(hello), 0);
            
            while (1) {
                
                memset(buffer, 0, BUFFER_SIZE);
                valread = read(new_socket, buffer, 1024 - 1); 

                printf("Client %d: %s\n", client_idx, buffer);

                if (strcmp(buffer, "exit") == 0) {
                    close(new_socket);
                    break;
                }

                send(new_socket, buffer, strlen(buffer), 0);

            }
        }
    }

    // closing the listening socket
    close(sfd1);
    return 0;
}

