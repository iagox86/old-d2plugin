#include "Command_commands.h"
#include "Command.h"

namespace cmd
{
	namespace process
	{	
		ProcessResult PacketLog::ProcessCommand( const Command::ArgList& args )	const
		{
			if ( args.size() == 0 || args[0] == "off")
			{
				// User didn't specify on or off, toggle it
				g_Variables["packetlog"] = "off";
			} 
			else 
			{
					g_Variables["packetlog"] = args[0];
			}

			// Print out a message for the user
			if(g_Variables["packetlog"] == "off")
				display(GREEN, "Packets will no longer be displayed.");
			else
				display(GREEN, "Packets are now being saved to %s", g_Variables["packetlog"].c_str());

			return success;
		}
	}
}

