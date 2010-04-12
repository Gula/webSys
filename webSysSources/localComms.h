/*
 * localComms.h
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#ifndef LOCALCOMMS_H_
#define LOCALCOMMS_H_

#include <stdlib.h>
#include "config.h"

//Prototypes:
int startLocalSocketServer(char* socketFile);
int serviceLocalSocket(int sock, char buffer[][MAX_CMD_LEN]);
void bufferCommand(char *command, char buffer[][MAX_CMD_LEN]);
int startLocalSocketClient(char *socketFile, char *data );

#endif /* LOCALCOMMS_H_ */
