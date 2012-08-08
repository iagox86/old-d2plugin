#include "LoseHealth.h"
#include "Display.h"
#include <stdio.h>
#include "Command.h"
#include "Send.h"

void __fastcall loseHealthProcess(int currentHealth)
{
	//display(ORANGE, "Your health is now %d", currentHealth);
	
	int minHealth = ParseFromString< int >( g_Variables["minhealth"] );

	if(currentHealth < minHealth) 
	{
		display(RED, "This would be a good time to leave" );
		leaveGame();
	}

	return;
}


void __declspec(naked) __fastcall loseHealth()
{
	__asm
	{
		mov ecx, esi
		shr ecx, 8
		call loseHealthProcess
		ret
	}
}




#include "Command_commands.h"
#include "Command.h"
#include "Display.h"

namespace cmd
{
	namespace process
	{
		ProcessResult MinHealth::ProcessCommand( const Command::ArgList& args ) const
		{
			if ( args.size() == 0 )
			{
				return invalidArgs; 
 
			} 
			else 
			{ 

				g_Variables["minhealth"] = ( args[0] );
				// set new minimum health
				display(CYAN, "The minimum health is now %d", ParseFromString < int > (g_Variables["minhealth"]));
			}

			return success;
		}
	}
}