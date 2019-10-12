#This work is licensed under a Creative Commons Attribution 4.0 International License.
#Author: Benedetto Marco Serinelli

all: Server_TCP Client_TCP 

Server_TCP: server.c
	gcc -o Server_TCP server.c

Client_TCP: client.c
	gcc -o Client_TCP client.c

clean:
	rm Server_TCP Client_TCP connection.txt random.txt