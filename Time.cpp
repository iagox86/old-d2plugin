#include "time.h"

#include <stdio.h>

char *timestamp(char buffer[9])
{
	time_t mytime; //time_t is a typedef for long
	tm *t; //tm is a struct declared in time.h which is similar to my m_time
	time(&mytime); //this make the value of mytime equal to the num of seconds after Jan 1 1970 
	t = localtime(&mytime); //this converts mytime to the already described struct

	sprintf(buffer, "%02d:%02d:%02d", t->tm_hour, t->tm_min, t->tm_sec);

	return buffer;
}

char *fulldate(char buffer[50])
{
	char *days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
	char *months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	time_t mytime; //time_t is a typedef for long
	tm *t; //tm is a struct declared in time.h which is similar to my m_time
	time(&mytime); //this make the value of mytime equal to the num of seconds after Jan 1 1970 
	t = localtime(&mytime); //this converts mytime to the already described struct
	
	sprintf(buffer, "%s, %s %02d, %04d", days[t->tm_wday], months[t->tm_mon], t->tm_mday, t->tm_year + 1900);

	return buffer;
}