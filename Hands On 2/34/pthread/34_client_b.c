//Name: Tejinder Singh
//Registration number: MT2022124

//34. Write a program to create a concurrent server.
//a. use fork
//b. use pthread_create
//Client side Program

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>

int main(void){
	int sd;
	int status;
	struct sockaddr_in server;

	char dataFromServer[128];

	sd= socket(AF_UNIX, SOCK_STREAM, 0);
	if(sd== -1){
		perror("Socket Creation:");
		_exit(0);
	}
	printf("Client side socket created successfully\n");

	server.sin_family= AF_UNIX;
	server.sin_port= htons(8080);
	server.sin_addr.s_addr= htonl(INADDR_ANY);

	status= connect(sd, (struct sockaddr *)&server, sizeof(server));
	if(status== -1){
		printf("Connection error:");
		_exit(0);
	}
	printf("Connection successfully established\n");

	read(sd, dataFromServer, sizeof(dataFromServer));
	printf("Data from server: %s\n", dataFromServer);

	//writing to the server
	write(sd, "Hello from Client\n", 18);

	printf("Data sent to the server\n");

	close(sd);

}
