#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define PORT 8080
#define MAX_EVENTS 10
#define BUFFER_SIZE 1024

// Function to set a socket to non-blocking mode
void set_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    fcntl(sock, F_SETFL, flags | O_NONBLOCK);
}

int main() {
    int server_fd, client_fd, epoll_fd, num_events, i;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct epoll_event ev, events[MAX_EVENTS];
    char* hello = "Hello from server";

    // Create server socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Set server socket to reuse address and port
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Set server socket to non-blocking
    set_nonblocking(server_fd);

    // Bind to port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, SOMAXCONN) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Create epoll instance
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    // Add server socket to epoll
    ev.events = EPOLLIN;
    ev.data.fd = server_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev) == -1) {
        perror("epoll_ctl: server_fd");
        exit(EXIT_FAILURE);
    }

    printf("Server is running on port %d\n", PORT);

    while (1) {
        num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (i = 0; i < num_events; i++) {
            if (events[i].data.fd == server_fd) {
                // Accept new client connection
                client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
                if (client_fd == -1) {
                    perror("accept");
                    continue;
                }

                // Set client socket to non-blocking mode
                set_nonblocking(client_fd);

                // Add client socket to epoll
                ev.events = EPOLLIN | EPOLLET; // Edge-triggered
                ev.data.fd = client_fd;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1) {
                    perror("epoll_ctl: client_fd");
                    close(client_fd);
                }

                send(client_fd, hello, strlen(hello), 0);
                printf("New client connected\n");

            } else {
                // Handle client data
                char buffer[BUFFER_SIZE];
                memset(buffer, 0, BUFFER_SIZE);
                int bytes_read = read(events[i].data.fd, buffer, BUFFER_SIZE - 1);
                if (bytes_read <= 0) {
                    // Client disconnected or error
                    printf("Client disconnected\n");
                    close(events[i].data.fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                } else {
                    printf("Received: %s", buffer);
                    write(events[i].data.fd, buffer, bytes_read); // Echo message back
                    sleep(5);
                    printf("Sent: %s", buffer);
                }
            }
        }
    }

    close(server_fd);
    close(epoll_fd);
    return 0;
}
