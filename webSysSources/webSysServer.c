/*
 * webSysServer.c
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "localComms.h"
#include "fileHandle.h"
#include "webSysAPI.h"
#include "config.h"
//----------------------------------------------------------------

int main(int argc, char *argv[])
{
	char socketFile[255] = {0};
	char zeroBuffer[MAX_CMD_LEN] = {0};
	int sock =0;
	
	int fd_json[MAX_JSON_FILES] = {0};
	int fdCounter = 0;
		
	int fd = open(CONF_FILE, O_RDONLY);
	if (fd > 0) {
		restartFile(fd);
		if (readFile(fd, socketFile)) {
			// Determine location of socket file
			return EXIT_FAILURE;
		} else {
			sock = startLocalSocketServer(socketFile);
			if (sock < 0) {
				return EXIT_FAILURE;
			}
		}
		
		int readVal;
		do {
			char dataFile[255] = {0};
			readVal = readFile(fd, dataFile);
			if (!readVal) {
				fd_json[fdCounter] = open(dataFile, O_RDWR | O_NOCTTY | O_NONBLOCK );
				if (fd_json[fdCounter] < 0) {
					printf("Error opening file %s.\n", dataFile);
					printf("Check that the file exists or edit %s\n", CONF_FILE);
					printf("%s exits now.\n", argv[0]);
					return EXIT_FAILURE;
				} else if (++fdCounter == MAX_JSON_FILES) {
					printf("Warning: The maximum number of JSON files supported (%d) has been\n", MAX_JSON_FILES);
					printf("reached. Any remaining JSON files listed in %s will be ignored.\n", CONF_FILE);
					break;
				}	
			} else if (readVal != BUF_MSG_EOF) {
				return EXIT_FAILURE;
			}
			
		} while (readVal != BUF_MSG_EOF);
		
		fd = close(fd);
	} else {
		return EXIT_FAILURE;
	}

	myProject_main_once(argc, argv, fdCounter, fd_json);

	while (1) {
		char cmdBuffer[MAX_CLIENTS][MAX_CMD_LEN] = {{0}};
		if (serviceLocalSocket(sock, cmdBuffer) > 0) {
			int i;
			for (i = 0; i < MAX_CLIENTS; i++) {
				if (memcmp(cmdBuffer[i],zeroBuffer,MAX_CMD_LEN)) {
					myProject_commands(cmdBuffer[i], fdCounter, fd_json);
				}
			}
		}

		myProject_main_loop(argc, argv, fdCounter, fd_json);
	}

	sock = close(sock);
	return EXIT_SUCCESS;
}
