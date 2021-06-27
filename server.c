#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 7979
#define ADDR "127.0.0.1"

void fatal_err(char *err_msg){
    perror(err_msg);
    exit(EXIT_FAILURE);
}

int main(void){
    char recv_buff[100];

    int server_running = 1;
    int connection_established = 1;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd == -1){ // socket() returns -1 on failure
        fatal_err("Failed to create socket");
    }

    if(inet_aton(ADDR, &serv_addr.sin_addr) != 1){
        fatal_err("[inet_aton] Failed to load address");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    socklen_t size = sizeof(struct sockaddr_in);

    if(bind(sock_fd, (struct sockaddr*)&serv_addr, size) == -1){ // returns -1 on failure
        fatal_err("Failed to bind socket");
    }

    if(listen(sock_fd, 5) == -1){
        fatal_err("Failed to listen for incoming connections");
        }

    printf("--- SERVER RUNNING ---\n");
    while (server_running) // while loop for accepting client connections
    {
        int new_sock_fd = accept(sock_fd, (struct sockaddr*)&client_addr, &size);
        if(new_sock_fd == -1){
            fatal_err("Failed to accept incoming connection");
        }
        while (connection_established)
        {
            recv(new_sock_fd, recv_buff, 100, 0); // man recv to see the full list of flags
            printf("%s\n", recv_buff);
            memset(recv_buff, 0, 100);
        }
        close(new_sock_fd);

    }


    close(sock_fd);

    return EXIT_SUCCESS;
}
