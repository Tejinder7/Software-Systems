//Name: Tejinder Singh
//Registration number: MT2022124

//33. Write a program to communicate between two machines using socket.
//Server side Program

#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>

int main(void){
	int sd, nsd;
	//nsd is the new socket descriptor that will be received after connection
	int bindStatus;
	int listenStatus;
	int clientSize;
	char dataFromClient[128];

	struct sockaddr_in server, client;

	sd= socket(AF_UNIX, SOCK_STREAM, 0);
	if(sd== -1){
		perror("Socket Creation:");
		_exit(0);
	}
	printf("Socket created successfully\n");

	server.sin_family= AF_UNIX;
	server.sin_port= htons(8080);
	server.sin_addr.s_addr= htonl(INADDR_ANY);

	bindStatus= bind(sd, (struct sockaddr *)&server, sizeof(server));
	if(bindStatus== -1){
		perror("Bind error:");
		_exit(0);
	}
	printf("Binding successful\n");

	listenStatus= listen(sd, 1);
	if(listenStatus== -1){
               	perror("Listen() error:");
                _exit(0);
        }
        printf("Listening for a socket ...\n");

	clientSize= (int)sizeof(client);

	nsd= accept(sd, (struct sockaddr *)&client, &clientSize);
	if(nsd== -1){
		perror("Connection error:");
		_exit(0);
	}

	write(nsd, "Hello from server\n", 18);

	read(nsd, dataFromClient, sizeof(dataFromClient));
	printf("Data from client: %s\n", dataFromClient);

	close(nsd);
	close(sd);
}
