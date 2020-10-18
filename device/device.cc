#include"Device.h"
#include <string.h>
#include <string> 

#include<iostream>

Device::Device(const char* str){
    name = str;
}

const char* Device::getName(){
    return name;
}


// @ SET
// SETTING property operationresult
void Device::setOperationResult( char* buffer ){

    // get parameter from request
    const char *commandParameterFromRequestBuffer = getWord('/',' ',buffer);
    
    // store value of command
    char command[20] = {0};
    strcat(command,commandParameterFromRequestBuffer);
    
    // get errors from somewhere
    const char *error = "computers starting hate humanity";

    // empty operationResult array
    std::fill( std::begin( operationResult ), std::end( operationResult ), 0 );

    // init operationResult ... as defined array
    const char init[10] = { 'C', 'o','m','m','a','n','d',' ','\"','\0'};
    for (int i =0; i < 10; i++ ){
        operationResult[i] = init[i];
    }

    // probably strcat needs a end first array, so we need to give an array with \0 at the end
    // add command
    strcat(operationResult, &command[0]);

    // further concatenations
    const char* concat2 = "\" to device ";
    strcat(operationResult, concat2);

    // insert device name
    strcat(operationResult, name);

    // define result
    if(0){
        const char* ok = " went good";
        strcat(operationResult, ok);
    }else{
        const char* no = " Error: ";
        strcat(operationResult, no);
        strcat(operationResult, error);
    }

    printf("IN DEVICE: %s",operationResult);
    // THIS FUNCTION JUST SET THE CLASS PROPERTY operationResult

};

// @ GET
// getting property of operation result throught class variable pointer
const char* Device::getOperationResult(){
 
    const char* pointer = &operationResult[0];
	return pointer;

}

const char* Device::getWord(const char startChar, const char endChar ,char *str){

    // init mechanic
	int i = 0;
	int record = 0;
	int offset = 0;

	// get modifiable array of chars
	char parameter[20];

	// if str[i]== endLine, endArray, out of array, GET OUT
	while(str[i] != '\0' && str[i] != '\n' ){

		// start record at /
		if(str[i] == startChar && !offset){
			i++;
			record = 1;
		}
		// if the parameter is not ended record..
		if (str[i] != endChar && record){
			parameter[offset] = str[i];
			offset++;
		}else{
			// as the parameter ends stop record
			record = 0;
		}
		i++;
	}

	// setend of array in memory slot
	parameter[offset]='\0';
    parameter[19]='\0';

    // give laocation of array to return
    const char* pointer = &parameter[0];
	return pointer;
}