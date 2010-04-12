/*
 * demo.h
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#ifndef DEMO_H_
#define DEMO_H_

#include <sys/time.h>

#define UPDATE_TIME 200 //ms

char tickNms(int nMs);
int timevalSubstract(struct timeval *result,struct timeval *x,struct timeval *y);
double systemModel(void);
void setSP(double sP);
void updateDataValues(int fd);

#endif /* DEMO_H_ */
