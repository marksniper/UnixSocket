/*
 *This work is licensed under a Creative Commons Attribution 4.0 International License.
 *Author: Benedetto Marco Serinelli
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>


#define PORT 53000	// port number
#define BACKLOG 10	//number of connections
#define BUFSIZE 256	//size of the message buffer
void saveInFile(char *buffer);
int main(int argc, char *argv[]) {

    int socket_fd;
    //create an endpoint for communication
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if( socket_fd == -1 )
        perror("Socket creation failed");
    else
        printf("Socket created\n");

    /* struttura server */
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    //set family address
    addr.sin_family = AF_INET;
    //set port
    addr.sin_port = htons(PORT);
    //INADDR_ANY is a constant that equal zero
    addr.sin_addr.s_addr = htons(INADDR_ANY);
    //bind a name to a socket
    if(bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
        perror("Error to bind socket");
    else
        printf("Bind OK\n");
    //listen for connections on a socket
    if(listen(socket_fd, BACKLOG) < 0)
        perror("Listen for connections on a socket failed");
    else {
        printf("Listen for connections on a socket... OK\n");
        printf("Server listens for connections on a port %d.\n", PORT);
    }

    //client struct
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    int quit = 0;
    int client;

    while(!quit) {
        //accept client connection
        client = accept(socket_fd, (struct sockaddr *)&client_addr, &len);
        if(client < 0)
            perror("Client connection was refused. Can not accept client connection");
        else {
            printf("Client connection is accepted\n");
            char client_addr_c[INET_ADDRSTRLEN] = "";
            inet_ntop(AF_INET, &(client_addr.sin_addr), client_addr_c, sizeof(client_addr));
            printf("New client connection from[IP:PORT] %s:%d.\n", client_addr_c, ntohs(client_addr.sin_port));
        }
        char buf[BUFSIZE];
        char buf_reply[BUFSIZE] = "Hi client :D";
        ssize_t n = 0;
        //receive message from client
        n = recv(client, buf, BUFSIZE-1, 0);
        if(n < 0) {
            perror("Message from client can't be received");
        } else if(n == 0)
            printf("Connection is closed by client.\n");
        else {
            //add null terminator, abbreviated NULL, at end part of buffer
            buf[n] = '\0';
            printf("Message was be received by client: %s. Message size in byte: %ld.\n", buf, sizeof(buf));
            saveInFile(buf); //save received message in file
            //send reply to client
            n = send(client, buf_reply, BUFSIZE - 1, 0);
            if(n < 0)
                perror("Message can't be sent");
            else if(n == 0)
                printf("Connection was be closed by client\n");
            else
                printf("Reply client with message. Message size in byte %d \n", (int)n);
        }
        //close client socket
        close(client);
    }
}
void saveInFile(char *buffer) {
    printf("Message: %s\n", buffer);
    FILE *fp = fopen("connection.txt", "a");
    if (fp != NULL) {
        //add timestamp before mesage
        time_t ltime; /* calendar time */
        ltime = time(NULL); /* get current cal time */
        //printf("%s",asctime(localtime(&ltime)));
        fputs(asctime(localtime(&ltime)), fp);
        fputs(buffer, fp);
        fputs("\n", fp);
        fclose(fp);
    } else {
        //create file
        FILE *fpNEW = fopen("connection.txt", "w");
        if (fpNEW != NULL) {
            perror("Impossible to create a file");
        } else {
            fclose(fpNEW);
            saveInFile(buffer);
        }
    }
}
