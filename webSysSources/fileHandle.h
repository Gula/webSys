/*
 * fileHandler.h
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#ifndef FILEHANDLE_H_
#define FILEHANDLE_H_

#include <stdlib.h>

//Return values for int readFile(int fd, char *lineRead)
#define BUF_MSG_ERR -1
#define BUF_MSG_ERR_FULL -2
#define BUF_MSG_EOF -3
#define BUF_MSG_COMPLETE 0
//----------------------------------------------------------------

//Prototypes:
void restartFile(int fd);
/* void restartFile(int fd) rewinds the file described by fd to its beginning.
 */
int readFile(int fd, char *lineRead);
/* int readFile(int fd, char *lineRead) reads a line from the file fd and puts it in
 * lineRead as a string. It skips sections between '#' and '\n'. It ignores spaces ' '.
 */
int updateDataFile(int fd, char *id, char *property, char *value);
/* int updateDataFile(int fd, char *id, char *property, char *value) finds the line in
 * the file fd that contains the 'id', and writes 'value' for the specified 'property'.
 */

#endif /* FILEHANDLE_H_ */
