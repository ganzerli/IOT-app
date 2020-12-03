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
// IN

// @ SET
// SETTING property operationresult
void Device::setOperationResult( char* buffer ){

    const int COMMANDCHARS = 4;

    // get parameter from request
    const char *commandParameterFromRequestBuffer = getWord('/',' ',buffer);
    
    // store value of command
    char command[COMMANDCHARS +1] = {0};
    command[5]= '\0';

    strcat(command,commandParameterFromRequestBuffer);
    
    // get errors from somewhere
    const char *error = "command not found";

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

    //
    //
    // function check for command


    int commandExists = 0;
    int allCommandsLength = 16;
    int commandLength = 4;

    // select command from commandlist
    for (int i=0; i < allCommandsLength; i+=commandLength ){
        printf("i = %i \n",i);


        for (int j =0 ; j < commandLength ; j++){
            if(commands[i+j] == command[j]){
                printf("%i) letter %c is in this place \n",j, commands[j]);
                commandExists++;
            }else{
                commandExists = 0;
                printf("%i) letter %c is not in this place \n",j, command[j]);
                j=0;
                break;
            }
            
        }
        if(commandExists >= commandLength){
            printf("command %s exists %i \n", &command[0], commandExists);
            break;
        }

    }

    //end function find commands
    const int functionReturnsTrue = commandExists >= commandLength;
    //

    // define result
    if(functionReturnsTrue){
        const char* ok = " went good";
        strcat(operationResult, ok);
    }else{
        const char* no = " Error: ";
        strcat(operationResult, no);
        strcat(operationResult, error);
    }

    //printf("IN DEVICE: %s",operationResult);
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