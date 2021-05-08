#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define PORT 7979
#define ADDR "127.0.0.1"
#define FLAGS 0


void die(char *err_msg){
    perror(err_msg);
    exit(EXIT_FAILURE);
}

int main(void){

    char recv_buff[100];
    char send_buff[100];

    int connection_established = 1;

    struct sockaddr_in serv_addr;
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

    if(connect(sock_fd, (struct sockaddr *)&serv_addr, size) == -1){
        die("Failed to connect");
    }
    recv(sock_fd, recv_buff, 100, FLAGS);
    printf("%s\n", recv_buff);
    while (connection_established)
    {
       scanf("%s", send_buff);
       send(sock_fd, send_buff, 100, FLAGS);

    }
    

    return EXIT_SUCCESS;

}
