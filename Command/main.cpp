#include "command.h"
#include "command_commands.h"
#include <iostream>

int main( void )
{
	cmd::CommandProcessor::CommandList commands;
	commands.push_back( new cmd::process::MinHealth( 25 ) );
	commands.push_back( new cmd::process::PacketDisplay( 0 ) );
	commands.push_back( new cmd::process::PacketLog( 1 ) );
	commands.push_back( new cmd::process::ReadMem() );
	commands.push_back( new cmd::process::WriteMem() );

	cmd::CommandProcessor g_CommandProcessor;
	g_CommandProcessor.Initialize( commands );
	cmd::ProcessResult result;
	result = g_CommandProcessor.ProcessCommand( "/writemem 32 32" );
	result = g_CommandProcessor.ProcessCommand( "/readmem 32 32" );
	result = g_CommandProcessor.ProcessCommand( "/minhealth 1337" );

	for ( std::map< std::string, DWORD >::iterator iter = g_Variables.begin(); 
		iter != g_Variables.end(); ++iter )
	{
		std::cout << iter->first << ": " << iter->second << std::endl;
	}

	std::cin.get();

	return 0;
}
