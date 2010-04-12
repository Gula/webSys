/*
 *  cgiScriptHandle.c
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cgiScriptHandle.h"
//---------------------------------------------------------

int cgiReceive(char *input, int maxLen)
{
// cgiReceive determines the method (POST or GET) used to pass data to the CGI script.
// It checks that the length of the data is shorter than the value of maxLen and stores
// the data in input. Returns:
// CGI_SUCCESS = Success,
// CGI_ERR_LEN_DATA = Failure, problems with the length of the data (possibly longer than maxLen),
// CGI_ERR_METHOD = Failure, method neither POST nor GET.

	char *contentLength;
	char *requestMethod;
	char *queryString;
	int lengthCmd;
	
	requestMethod = getenv("REQUEST_METHOD");
	
	if (requestMethod==NULL) {
		return CGI_ERR_METHOD;
	} else if (!strcmp(requestMethod, "POST")) {
		//Method is POST
		contentLength = getenv("CONTENT_LENGTH");
		if ((contentLength == NULL) || sscanf(contentLength,"%i",&lengthCmd)!=1 || lengthCmd > maxLen) {
			return CGI_ERR_LEN_DATA;
		} else {
			fgets(input, lengthCmd + 1, stdin);	//Store in 'input' the command coming in stdin
		}
	} else if (!strcmp(requestMethod, "GET")) {
		//Method is GET
		queryString =  getenv("QUERY_STRING");
		if((queryString == NULL) || !(lengthCmd = strlen(queryString)) || lengthCmd > maxLen) {
			return CGI_ERR_LEN_DATA;
		} else {
			strncpy(input, queryString, lengthCmd + 1);	//Store in 'input' the command coming in QUERY_STRING
		}
	} else {
		return CGI_ERR_METHOD;
	}

	return CGI_SUCCESS;
}
//---------------------------------------------------------

void cgiUnencode(char *src, char *last, char *dest)
{ 	// Unencode POST command sent by the web browser
	// '+' --> ' '

	while (src != last) {
		if (*src == '+') {
			*dest = ' ';
		} else if (*src == '%') {
			int code;
			if (sscanf(src + 1, "%2x", &code) != 1) {
				code = '?';
			}
			*dest = code;
			src += 2;
		} else {
			*dest = *src;
		}
		 src++;
		 dest++;
	}
	*dest = '\n';
	*++dest = '\0';
}
//---------------------------------------------------------
