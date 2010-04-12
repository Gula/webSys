/*
 * webSysAPI.h
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#ifndef WEBSYSAPI_H_
#define WEBSYSAPI_H_

void myProject_commands(char *cmdBuffer, int fdCounter, int *fd_json);
int myProject_main_once(int argc, char *argv[], int fdCounter, int *fd_json);
int myProject_main_loop(int argc, char *argv[], int fdCounter, int *fd_json);

#endif /* WEBSYSAPI_H_ */
