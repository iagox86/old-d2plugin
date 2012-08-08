#include "ProcessChat.h"
#include "Display.h"

static const int BNETHANDLE = 0;

// This function will be called every time the user types a message beginning with
// a '/' and presses <enter>.
BOOL __fastcall processChat(char *message)
{
	if(stricmp(message, "/whoami") == 0)
	{
		display(message, GOLD);
		return !BNETHANDLE;
	}

	return BNETHANDLE;
	
}

#include <string>
#include "Command.h"

// The ProcessChat class
void ProcessChat::addCommand(Command *newCommand)
{
	commands[newCommand->getCommand()] = *newCommand;
}

// This gets a command like, "/sethealth 6", which it has to break up.
void ProcessChat::processCommand(std::string str)
{
	std::string::size_type size = str.find(' ');

	std::string command;
	std::string parameters;

	if(size != std::string::npos)
	{
		command = str.substr(0, size);
		command = str.substr(size, str.length());
	}
	else
	{
		command = str;
		parameters = "";
	}
}