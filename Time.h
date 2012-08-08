#pragma once

/***
*time.h - A class and struct for use with time and dates
*
* struct mtime contains various elements of time and date you can use
* Reset() will refresh the values in the mtime struct
* Time and Date will be returned as a string using their repective functions
*
*		copyright 3/25/2002 by Matthew Guidry
***/

#include <time.h>

char *timestamp(char buffer[9]);
char *fulldate(char buffer[50]);


