/*
 * fileHandle.c
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "fileHandle.h"

#define MAX_LINE_LEN 80
//----------------------------------------------------------------

void restartFile(int fd)
{
	lseek(fd, 0, SEEK_SET);
}
//----------------------------------------------------------------

int readFile(int fd, char *lineRead)
{
	int retVal = BUF_MSG_ERR;
	// Read the file into the buffer.
	int nChars = 0;
	char ignoreText = 0;

	while (1) {
		char byte;
		if (read(fd, &byte, 1)) {
			if (byte == '#') {
				ignoreText = 1;
			} else if (byte == '\n') {
				if(nChars) {
					*(lineRead + nChars) = 0; //add 0 to have a string
					retVal = BUF_MSG_COMPLETE;
					break;
				} else {
					ignoreText = 0;
				}
			} else if (((byte !='\r')||(byte !=' '))&&(!ignoreText)) {
				// ignore <CR> and spaces
				*(lineRead + nChars) = byte;
				if (nChars == MAX_LINE_LEN - 1) {
					retVal = BUF_MSG_ERR_FULL;
					break;
				}
				nChars++;
			}
		} else {
			//EOF
			fd = close(fd);//close the file descriptor and make the file descriptor = 0 (close normally returns 0)
			retVal = BUF_MSG_EOF;
			break;
		}
	}

	lseek(fd, 0, SEEK_CUR);

	return retVal;
}
//----------------------------------------------------------------

int updateDataFile(int fd, char *id, char *property, char *value)
{
	int count = 0;
	int offsetInFile = 0;
	char buffer[MAX_LINE_LEN] = {0};

	restartFile(fd);//Rewind File

	while(1) {
		if (!read(fd, buffer + count, 1)) {
			return EXIT_FAILURE;
		} else {
			if (*(buffer + count++)=='\n') {
				if (strstr(buffer, id)!=NULL) {
					char *offset;
					offset = strstr(buffer, property);
					if (offset!=NULL) {
						char *fieldStart;
						fieldStart = offset + strlen(property) + 3;
						int offsetInLine = fieldStart - buffer;
						lseek (fd, (off_t)(offsetInFile + offsetInLine), SEEK_SET);
						write(fd, value, strlen(value));
						return EXIT_SUCCESS;	//skip inspecting the rest of the file
					}
				}
				offsetInFile += count + 1;
				count = 0;
				memset(buffer, 0, MAX_LINE_LEN);
				lseek (fd, (off_t)offsetInFile, SEEK_SET);
			} else if (count >= MAX_LINE_LEN) {
				return EXIT_FAILURE;
			}
		}
	}
}
//----------------------------------------------------------------
