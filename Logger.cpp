#include <stdio.h>
#include <stdarg.h>

#include "Command_commands.h"
#include "Constants.h"
#include "Display.h"
#include "Logger.h"
#include "Time.h"

Logger::Logger(char *filename)
{
	this->filename = filename;

	FILE *file = fopen(filename, "a");

	if(filename != NULL)
	{
		char Fulldate[50];
		fprintf(file, "----------------------------\n");
		fprintf(file, "Session beginning\n");
		fprintf(file, "%s\n", fulldate(Fulldate));
		fprintf(file, "%s\n", timestamp(Fulldate));
		fprintf(file, "----------------------------\n");
	}
}

Logger::~Logger()
{
	FILE *file = fopen(filename, "a");

	if(file != NULL)
	{
		char Fulldate[50];
		fprintf(file, "----------------------------\n");
		fprintf(file, "Session ending\n");
		fprintf(file, "%s\n", fulldate(Fulldate));
		fprintf(file, "%s\n", timestamp(Fulldate));
		fprintf(file, "----------------------------\n\n\n\n");
		fclose(file);
	}
}

void Logger::add(const char *format, ...)
{
	FILE *file = fopen(filename, "a");

	if(file != NULL)
	{
		// Displays on the screen, using printf style format
		char OutStr[512];
		va_list argptr;
		va_start(argptr, format);
		//vsprintf(OutStr, format, argptr);
		vsprintf(OutStr, format, argptr);

		char Timestamp[9];
		fprintf(file, "[%s] %s\n\n", timestamp(Timestamp), OutStr);

		fclose(file);
	}
}

namespace cmd
{
	namespace process
	{	
		ProcessResult Log::ProcessCommand( const Command::ArgList& args )	const
		{
			if ( args.size() == 0 )
			{
				return invalidArgs; 
 
			} 
			else  
			{ 
				std::string str;

				for(DWORD i = 0; i <  args.size(); i++)
				{
					str = str + args[i] + " ";
				}

				mylog.add(str.c_str() );
				display(CYAN, "Added to log: %s", str.c_str());
			}
			return success;
		}
	}
}