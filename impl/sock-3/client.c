// Client side C program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENT_MSG_LEN 200
#define PORT 8080


int main(int argc, char const* argv[])
{
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[BUFFER_SIZE] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary
    // form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }

    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    valread = read(client_fd, buffer, 1024 - 1);
    printf("Server says: %s\n", buffer);


    while (1) {
        char client_msg[MAX_CLIENT_MSG_LEN];
        printf("Your message: ");
        fgets(client_msg, MAX_CLIENT_MSG_LEN, stdin);

        send(client_fd, client_msg, strlen(client_msg), 0);

        if (strcmp(client_msg, "exit\n") == 0) {
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);
        valread = read(client_fd, buffer, 1024 - 1);
        // subtract 1 for the null terminator at the end
        printf("Server says: %s\n", buffer);

    }

    // closing the connected socket
    close(client_fd);
    return 0;
}

