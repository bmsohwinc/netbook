// Server side C program to demonstrate Socket
// programming
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <asm-generic/socket.h>
#include <sys/select.h>

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


    fd_set curr_sockets, ready_sockets;
    FD_ZERO(&curr_sockets);
    FD_SET(sfd1, &curr_sockets);




    

    int client_idx = 0;

    int clients[MAX_CLIENTS] = { 0 };

    while (client_idx < MAX_CLIENTS) {

        ready_sockets = curr_sockets;

        if (select(FD_SETSIZE, &ready_sockets, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < FD_SETSIZE; i++) {
            if (FD_ISSET(i, &ready_sockets)) {
                if (i == sfd1) {
                    if ((new_socket
                        = accept(sfd1, (struct sockaddr*)&address,
                                &addrlen))
                        < 0) {
                        perror("accept");
                        exit(EXIT_FAILURE);
                    }
            
                    clients[client_idx] = new_socket;
                    client_idx++;

                    printf("New connection, socket fd is %d, index %d\n", new_socket, client_idx);
            
                    FD_SET(new_socket, &curr_sockets);

                    send(new_socket, hello, strlen(hello), 0);
            
                    
                } else {
                    char buffer[1024] = { 0 };
                    memset(buffer, 0, BUFFER_SIZE);
                    valread = read(i, buffer, 1024 - 1); 

                    printf("Client %d: %s\n", i, buffer);

                    if (strcmp(buffer, "exit") == 0) {
                        close(i);
                        break;
                    }

                    sleep(5); // shows that this blocks until server finishes client request

                    send(i, buffer, strlen(buffer), 0);

                }
            }
        }
    }

    // closing the listening socket
    close(sfd1);
    return 0;
}

