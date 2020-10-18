// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <string> 
// import porject classes
//#include "device/Device.h"
#include "class_server/Server.h"


int Server::serve(int port , const char* hello, Device *device) { 

	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 

	// application/json;charset=utf-8
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 

	// Forcefully attaching socket to the port 8080 
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) { 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 

	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( port ); 

	// Forcefully attaching socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0){ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	if (listen(server_fd, 3) < 0) { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 

    // keep server on
	while(1){

	    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) { 
	    	perror("accept"); 
	    	exit(EXIT_FAILURE); 
	    } 

        //if connection , read value from client call
        valread = read( new_socket , buffer, 1024); 

		// Takes the parameter in the request after / and sets if the operation went good with the command found in the http request (buffer);
		device->setOperationResult(&buffer[0]);

		// get the message if the command went ok from device class
		const char* payload = &device->getOperationResult()[0];

		//const char* hello1 = (server) getHttpResponse(hello1);
		const char *fullHttpResponse = getHttpResponse(payload);

		// send response to client
	    send(new_socket , fullHttpResponse , strlen(fullHttpResponse) , 0 );
	
	    printf("Message sent to client\n");
	 }

	return 0; 
} 

const char* Server::getHttpResponse(const char* payload){

	char resp [1024] = {0};
	const char *init = "HTTP/1.1 200 OK\r\nServer: nginx\r\nDate: Mon, 12 Oct 2020 20:37:51 GMT\r\nContent-Type: tetx/html\r\nContent-Length: ";

	//Init resp
	strcat(resp, init);

	// get payload length
	int len = strlen(payload);
	std::string lenS = std::to_string(len);
	// add payload size
	strcat(resp, &lenS[0]);

	// add end of http headers
	strcat(resp , 
		"\r\nConnection: close\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Credentials: true\r\n\n"
	);

	//add payload
	strcat(resp, payload);
	//end http string
	strcat(resp, "\r\n\0");

	// return pointer to full http response
	const char *pointer = &resp[0];
	return pointer;
}
