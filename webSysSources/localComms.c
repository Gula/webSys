/*
 * localComms.c
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

#include "localComms.h"

fd_set active_fd_set;
struct sockaddr_un clientName;
//----------------------------------------------------------------

int startLocalSocketServer(char* socketFile)
{ 
	unlink(socketFile);	// Remove the filename first, it's ok if the call fails
	clientName.sun_family = AF_LOCAL;
	strcpy(clientName.sun_path, socketFile);
	int sock = socket(PF_LOCAL, SOCK_STREAM, 0);

	if (sock == -1) {
		perror("socket");
		return EXIT_FAILURE;
	}
	if (bind(sock, (struct sockaddr *)&clientName, 1 + SUN_LEN(&clientName))== -1) {
		perror("bind");
		return EXIT_FAILURE;
	}
	if (chmod(socketFile, (S_IRWXO | S_IRWXU))== -1) {
	//change permissions for the socket so the client can connect
		perror("chmod");
		return EXIT_FAILURE;
	}
	if (listen(sock, 10) == -1) {
		perror("listen");
		return EXIT_FAILURE;
	}
	// Initialize the set of active sockets.
	FD_ZERO(&active_fd_set);
	FD_SET(sock, &active_fd_set);

	return sock;
}
//----------------------------------------------------------------

int serviceLocalSocket(int sock, char buffer[][MAX_CMD_LEN])
{
	fd_set read_fd_set;
	int newSock;
	socklen_t size;

	struct timeval timeOut;
	int i;
	int cmdCounter = 0;

	timeOut.tv_sec = 0;
	timeOut.tv_usec = 0;

	read_fd_set = active_fd_set;
	if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, &timeOut) < 0) {
		perror("select");
		return EXIT_FAILURE;
	}

	// Service all the sockets with input pending.
	for (i = 1; i < FD_SETSIZE; i++) {
		if (FD_ISSET(i, &read_fd_set)) {
			if (i == sock) {
				// Connection request on original socket.
				size = sizeof(clientName);
				newSock = accept(sock,(struct sockaddr *) &clientName, &size);
				if(newSock < 0) {
					perror("accept");
					return EXIT_FAILURE;
				}
				FD_SET(newSock, &active_fd_set);
			} else {
				//Data arriving on an already-connected socket.
				signed char uno;
				char command[MAX_CMD_LEN] = {0};
				uno = recv(i, command, MAX_CMD_LEN, 0);
				if (uno == -1) {
					perror("recv");
					close(i);
					FD_CLR(i, &active_fd_set);
				} else {
					bufferCommand(command, buffer);	//buffers the command
					cmdCounter++;
				}
			}
		}
	}
	return cmdCounter;
}
//---------------------------------------------------------------

void bufferCommand(char *command, char buffer[][MAX_CMD_LEN])
{
	static int cmdPointer = 0;
	int i = 0;
	while (i < MAX_CMD_LEN) {
		buffer[cmdPointer][i] = command[i];
		i++;
	}
	cmdPointer++;
	cmdPointer &= (MAX_CLIENTS - 1);
}
//---------------------------------------------------------------

int startLocalSocketClient(char *socketFile, char *data )
{//Start the local-socket client and pass the command to the local-socket server
	int sock;
	struct sockaddr_un saddr;
	sock = socket(PF_LOCAL, SOCK_STREAM, 0);
	saddr.sun_family = AF_LOCAL;
	strcpy(saddr.sun_path, socketFile);
	if ((connect(sock, (struct sockaddr*)&saddr, SUN_LEN(&saddr)+1))<0) {
		perror("connect");
		return EXIT_FAILURE;
	}
	send(sock, data, strlen(data) + 1,0);	//pass the command to the local-socket server

	return EXIT_SUCCESS;
}
