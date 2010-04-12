/*
 * webSysAPI.c
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "webSysAPI.h"

// Add here the header files that are necessary for your custom process:
#include "demo.h"
//----------------------------------------------------------------

void myProject_commands(char *buffer, int fdCounter, int *fd_json)
{  /* This function is called every time the web browser sends a command
	* to the custom process. The commands have the form "cmdXX=...", where
	* XX identifies the command. For each command, a function from your
	* custom process should be called to deal with the command.
	* fdCounter is the number of file json files available. fd_json is an array 
	* of file descriptors. fd_json[0] is the fd for the first json file listed in
	* webSys.conf.
	*/
	printf("%s", buffer);
	if (!strncmp(buffer,"cmd00=",6)) {
		// Call custom function
		setSP(strtod(buffer + 6, NULL));
	} else if (!strncmp(buffer,"cmd01=",6)) {
		// Call custom function
	} else if (!strncmp(buffer,"cmd02=",6)) {
		// Call custom function
	} 	// ...
}
//----------------------------------------------------------------

int myProject_main_once(int argc, char *argv[], int fdCounter, int *fd_json)
{	/* This is part of the main() function for your custom process.
	* This function is called only once at the beginning of webSysServer.
	* Your functions that are called only once in the main() should be
	* placed here (e.g. initialisation functions). 
	* Notice that if your custom process requires command-line arguments, 
	* these can be passed when launching webSysServer.
	* fdCounter is the number of file json files available. fd_json is an array 
	* of file descriptors. fd_json[0] is the fd for the first json file listed in
	* webSys.conf.
	*/
	
	return EXIT_SUCCESS;
}
//----------------------------------------------------------------

int myProject_main_loop(int argc, char *argv[], int fdCounter, int *fd_json)
{	/* This is part of the main() function for your custom process.
	* This function is called within a 'while (1) {}' loop in webSysServer.
	* Your functions that are continuously called in the main() should be
	* placed here. 
	* Notice that if your custom process requires command-line arguments, 
	* these can be passed when launching webSysServer.
	* fdCounter is the number of file json files available. fd_json is an array 
	* of file descriptors. fd_json[0] is the fd for the first json file listed in
	* webSys.conf.
	*/
	
	if (tickNms(UPDATE_TIME)) {
		int i;
		for (i=0;i<fdCounter;i++) {
			updateDataValues(fd_json[i]);
		}	
	}

	return EXIT_SUCCESS;
}
//----------------------------------------------------------------
