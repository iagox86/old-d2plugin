#include "Command_commands.h"
#include "Command.h"
#include "Display.h"

namespace cmd
{
	namespace process
	{
		ProcessResult Test::ProcessCommand( const Command::ArgList& args ) const
		{
			display(BLUE, "Test function working.");
			return success;
		}
	}
}