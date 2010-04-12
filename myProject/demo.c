/*
 * demo.c
 *
 *  Created on: 02/04/2010
 *      Author: José Mare (josmare@gmail.com)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>

#include "fileHandle.h"

#include "demo.h"
//----------------------------------------------------------------

float setPoint = 0;
//----------------------------------------------------------------

double systemModel(void)
{
	static double x1 = 0;
	static double x2 = 0;
	static double integ = 0;

	double y = x1 - x2 + 0.05*random()/RAND_MAX;
	double err = setPoint - y;
	integ = err + integ;
	double u = integ*0.5 + 0.4*err;

	x1 = x1 + x2 + u ;
	x2 =  0.4*x2;
	return y;
}
//----------------------------------------------------------------

void setSP(double sP)
{
	setPoint = sP;
}
//----------------------------------------------------------------

void updateDataValues(int fd)
{
	char value[10] = {0};

		snprintf(value,10,"%03.6f",(float)random()/RAND_MAX*360);
		updateDataFile(fd, "Sensor 0", "value", value);

		memset(value,0,10);
		snprintf(value,10,"%03.6f", systemModel());
		updateDataFile(fd, "Sensor 1", "value", value);
}
//----------------------------------------------------------------

char tickNms(int nMs)
{
	char tick;
	static char firstRun = 1;
	static struct timeval time0;
	struct timeval time1;
	struct timeval timeDiff;

	tick = 0;

	if (firstRun) {
		gettimeofday(&time0, NULL);	//set initial time to calculate the time elapsed between samples
		firstRun = 0;
	} else {
		//set final time
		gettimeofday(&time1, NULL);
		timevalSubstract(&timeDiff,&time1,&time0);
		if (timeDiff.tv_usec >= nMs*1000) {
			time0 = time1;
			tick = 1;
		}
	}
	return tick;
}
//----------------------------------------------------------------

int timevalSubstract(struct timeval *result,struct timeval *x,struct timeval *y)
{
// Subtract the `struct timeval' values X and Y, storing the result in RESULT.
// Return 1 if the dfference is negative, otherwise 0.

	// Perform the carry for the later subtraction by updating y.
	if (x->tv_usec < y->tv_usec) {
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
		y->tv_usec -= 1000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > 1000000) {
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec;
		y->tv_sec -= nsec;
	}
	// Compute the time remaining to wait. tv_usec is certainly positive.
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;
	// Return 1 if result is negative.
	return x->tv_sec < y->tv_sec;
}
//----------------------------------------------------------------
