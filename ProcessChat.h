#ifndef PROCESS_CHAT_H
#define PROCESS_CHAT_H

typedef int BOOL;

#include <map>
#include "Command.h"

BOOL __fastcall processChat(char *message);

class ProcessChat
{
private:
	std::map <std::string, Command> commands;

public:
	// Add a command to the class
	void addCommand(Command *newCommand);

	// Process a textstring spoken by the users
	void processCommand(std::string str);
};

#endif