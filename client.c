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
#define PORT 53000	//port number
#define BACKLOG 10	//number
#define BUFSIZE 256	//size of the message buffer
#define SERVER_IP "127.0.0.1" //server IP address
void openFileAndWriteReadRandomNumber();
void openAndPrintContent();
void saveAllFileContentInsideVariable();
int main(int argc, char *argv[]) {

	int socket_fd;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if( socket_fd == -1 )
		perror("Socket creation failed");
	else
		printf("Socket created\n");
	//define server address and port in order to establish connection 
	struct sockaddr_in addr; 
	//set address 0.0.0.0
	memset(&addr, 0, sizeof(addr));
	//set family address 
	addr.sin_family = AF_INET;
	//set port
	addr.sin_port = htons(PORT);
    //convert IPv4 address from text to binary form
    if(inet_pton(AF_INET, SERVER_IP, &(addr.sin_addr.s_addr)) < 0)
		perror("inet_pton() failed");
	
	socklen_t len = sizeof(addr);
	
	//connect to server
	int server_fd;
	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	//create socket
	if(server_fd < 0)
		perror("Socket can't be created");
	else
		printf("Socket is created successfully\n");
	
	//establish connection
	if(connect(server_fd, (struct sockaddr *)&addr, len) < 0)
		perror("Connection can't be established");
	else
		printf("Connection is established.\n");
		
	//prepare  message
	char buff_message[BUFSIZE] = "";
	ssize_t sent_byte = 0;
	ssize_t receeive_byte = 0;
	
	snprintf(buff_message, BUFSIZE - 1, "Hello server :)"); //format and store a series of characters and values in the array buffer.
	//sleep one 1 second
	sleep(1);
	//send message
	sent_byte = send(server_fd, buff_message, strlen(buff_message), 0);
	
	if(sent_byte < 0)
		perror("Message can't be sent");
	else
		printf("Message was sent. Message size in byte: %d\n", (int)sent_byte);
	
	//Receive message from server
	receeive_byte = recv(server_fd, buff_message, BUFSIZE - 1, 0);
	if(receeive_byte < 0) {
		perror("Message from server can't be received");
	}
	else {
		if(receeive_byte == 0)
			printf("Close connection with server\n");
		else if (receeive_byte > 0)
			printf("Message from server: %s\n", buff_message);
	}
	close(server_fd);
    openFileAndWriteReadRandomNumber();
    openAndPrintContent();
    saveAllFileContentInsideVariable();
    exit(0);
}
void openFileAndWriteReadRandomNumber() {
    char str[10];
    FILE *fp;
    fp = fopen("random.txt", "w");
    if (fp == NULL) {
        printf("Impossible to open a file");
        exit(1);
    }
    for (int i = 0; i < 10; ++i) {
        fprintf(fp, "%d", rand() % 10);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void openAndPrintContent() {
    FILE *fp;
    fp = fopen("random.txt", "r");
    if (fp == NULL) {
        printf("Impossible to open a file");
        exit(1);
    }
    char content = fgetc(fp);
    printf("*** FILE CONTENT ***\n");
    while (content != EOF) {
        printf("%c", content);
        content = fgetc(fp);
    }
    printf("*** END FILE CONTENT ***\n");
    fclose(fp);
}
void saveAllFileContentInsideVariable(){
    printf("*** PRINT FILE CONTENT 2 ***\n");
    char * buffer = 0;
    long length;
    FILE *fp;
    fp = fopen("random.txt", "r");
    if (fp == NULL) {
        printf("Impossible to open a file");
        exit(1);
    }
    if (fp){
        fseek (fp, 0, SEEK_END);
        length = ftell (fp);
        fseek (fp, 0, SEEK_SET);
        buffer = malloc (length);
        if (buffer)
        {
            fread (buffer, 1, length, fp);
        }
        fclose (fp);
    }

    if (buffer)
    {
        // start to process your data / extract strings here...
        printf("Content: %s\n", buffer);
    }
}

