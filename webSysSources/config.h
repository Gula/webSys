/*
 * config.h
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#define CONF_FILE "./webSys.conf" // webSys Configuration file

#define MAX_CMD_LEN 80 // Maximum length of a command
#define MAX_CLIENTS 4 // Maximum number of clients that can connect simultneously.This has to be a power of 2 (circular buffer).

#define MAX_JSON_FILES 10 // Maximum number of JSON files supported

#endif /* CONFIG_H_ */
