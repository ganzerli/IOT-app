// Server side C/C++ program to demonstrate Socket programming 
#include <string>
#include <iostream>
//#include "device/Device.h"
#include "class_server/Server.h"



int main(int argc, char const *argv[]) { 

	printf("!!! INIT !!! -> ADD AS ARG THE NAME OF THE DEVICE!!");
	const char* name = argv[1];
	Device device(name);
	// const name persists in server because declared in this context

	//std::cout << device.getName() << std::endl;

	const char *resp;
	Server server;

	int a = server.serve(3001 , resp, &device );

	return 0; 
} 
