#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


#define PORT 7979
#define ADDR "127.0.0.1"
#define FLAGS 0

void die(char *err_msg){
    perror(err_msg);
    exit(EXIT_FAILURE);
}


int main(void){
    char *welcome = "Welcome, enter a command";
    char recv_buff[100];
    char hostname[20];
    if(gethostname(hostname, 20) == -1){
        die("Failed to retrieve hostname");
    }
    int server_running = 1;
    int connection_established = 1;


    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;

    socklen_t size = sizeof(struct sockaddr_in);
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(sock_fd == -1){
        die("Failed to create socket");
    }

    if(inet_aton(ADDR, &serv_addr.sin_addr) != 1){
        die("[inet_aton] Failed to load address");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    int ret = bind(sock_fd, (struct sockaddr*)&serv_addr, size);
    if(ret == -1){
        die("Failed to bind socket");
    }

    if(listen(sock_fd, 5) == -1){
    die("Failed to listen for incoming connections");
    }

    printf("--- SERVER RUNNING ---\n");
    while (server_running) // implement time frames for server_running
    {
        int new_sock_fd = accept(sock_fd, (struct sockaddr*)&client_addr, &size);
        if(new_sock_fd == -1){
            die("Failed to accept incoming connection");
        }
        printf("[Client Connection] %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port)); 
        send(new_sock_fd, welcome, 25, FLAGS); // send initial welcome message to client
        while (connection_established)
        {
            recv(new_sock_fd, recv_buff, 100, FLAGS);
            // parse command and send response
            printf("%s\n", recv_buff); // as of now only prints recv buffer
        }
        
    }

    return EXIT_SUCCESS;
}
