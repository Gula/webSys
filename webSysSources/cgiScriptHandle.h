/*
 * cgiScriptHandle.h
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#ifndef CGISCRIPTHANDLE_H_
#define CGISCRIPTHANDLE_H_

#define CGI_SUCCESS 0
#define CGI_ERR_LEN_DATA 1 //problems with the length of the data (possibly longer than maxLen).
#define CGI_ERR_METHOD 2 //method neither POST nor GET.

int cgiReceive(char *input, int maxLen);
void cgiUnencode(char *src, char *last, char *dest);

#endif /* CGISCRIPTHANDLE_H_ */
