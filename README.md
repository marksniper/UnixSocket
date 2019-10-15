# UNIX Socket
Unix socket is made up of two file, written in C, defined as follow:
1. _server.c_: 
    * open socket
    * listen continuously socket, waiting connection from **client**
    * receive message from client and print on standard output the message
    * save received message in _connection.txt_, if file doesn't exist, server provides to create its
    * send response to client
2. _client.c_ :
    * open socket in order to communicate to server
    * send message to server
    * receive message from server
    * close socket 
    * open file and write 10 random number in _random.txt_, if file doesn't exist, client provides to create its
    * print content character by character
    * read all file content and print buffer variable as string
## LINKS
[Advanced Programming in the UNIX Environment](https://zodml.org/sites/default/files/Advanced_Programming_in_the_UNIX_Environment%2C_3rd_Edition.pdf)
[Understand inet](https://stackoverflow.com/questions/1593946/what-is-af-inet-and-why-do-i-need-it)
[Developing C programs on Mac OS](https://www.cs.auckland.ac.nz/~paul/C/Mac/)
## TEST
Use _Makefile_ to test code
Compile: move in directory when the code is stored, with 
```bash
cd PATH
```
Launch make command
```bash
make
```
Launch server
```bash
./Server_TCP 
```
Launch client
```bash
./Client_TCP
```
Clean 
```bash
make clean
```
## Authors
* **Benedetto Marco Serinelli** - *Initial work* 
## Acknowledgments
The code is tested only on _Ubuntu 18.04.3 LTS_ and _macOS 10.13_.
