#pragma once

#include <stdio.h>
#include <stdlib.h>

class Logger
{
private:
	char *filename;

public:
	Logger(char *filename);
	~Logger();

	void Logger::add(const char *format, ...);
};
