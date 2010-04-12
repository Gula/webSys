/*
 * webSysClient.c
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
#include "cgiScriptHandle.h"
#include "fileHandle.h"
#include "config.h"
//----------------------------------------------------------------

#define EXTRA 6 // 5 for field name "cmdXX" (cmd00~cmd99, if required)
				// 1 for "="
#define MAXLEN 80
#define MAXINPUT MAXLEN + EXTRA + 2 // 1 for added line break, 1 for trailing NUL
//----------------------------------------------------------------

int main(void)
{
	char socketFile[255] = {0};

	int fd = open(CONF_FILE, O_RDONLY);
	if (fd > 0) {
		restartFile(fd);
		if (readFile(fd, socketFile)) {
			// Determine location of socket file
			 return EXIT_FAILURE;
		}
		fd = close(fd);
	}

	char input[MAXINPUT]={0};
	char data[MAXINPUT]={0};

	if (!cgiReceive(input, MAXLEN))
		cgiUnencode(input, input + strlen(input), data);
	else
		return EXIT_FAILURE;

	startLocalSocketClient(socketFile, data);
	printf("Content-Type: text/plain;charset=us-ascii\n\n");

	return EXIT_SUCCESS;
}
