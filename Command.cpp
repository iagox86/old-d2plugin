#include "command.h"
#include "command_commands.h"
#include "StringTokenizer.h"
#include "Display.h"

typedef std::map< std::string, std::string > VariableMap;
VariableMap g_Variables;
cmd::CommandProcessor g_CommandProcessor;

void InitFullCommandProcessor()
{
	cmd::CommandProcessor::CommandList commandList;
	commandList.push_back( new cmd::process::MinHealth( "25" ) );
	commandList.push_back( new cmd::process::PacketDisplay( "off" ) );
	commandList.push_back( new cmd::process::Test( ));
	commandList.push_back( new cmd::process::Log( ));

	// add more here

	g_CommandProcessor.Initialize( commandList );
}

bool SyncVariables( const std::string& varFile, bool load )
{
	std::string key, value;

	if ( load )
	{
		// loading variables, clear existing
		g_Variables.clear();

		std::ifstream fin( varFile.c_str() );
		if ( fin.is_open() )
		{
			while ( std::getline( fin, key ) && std::getline( fin, value ) )
			{
				g_Variables[key] = value;
			}

			fin.close();
			return true;
		}
		return false;
	} else {

		std::ofstream fout( varFile.c_str() );
		if ( fout.is_open() )
		{
			for ( VariableMap::iterator iter = g_Variables.begin();
				iter != g_Variables.end(); ++iter )
			{
				fout << key << std::endl << value << std::endl;
			}

			fout.close();
			return true;
		}
		return false;
	}
	
	// compiler will probably bark 
	//return false;
}

bool LoadAliases( const std::string& aliasFile )
{
	std::ifstream fin( aliasFile.c_str() );
	if ( fin.is_open() )
	{
		std::string in;
		while ( std::getline( fin, in ) )
		{
			// Skip blank lines and comments
			if ( in.size() < 3 || in[0] == ';' )
				continue;

			StringTokenizer tokens( in, "|" );
			std::string alias = tokens[0];
			std::string realCommand( tokens[1].begin() + 1, tokens[1].end() );

			// still don't understand why the hell you need this...
			//DWORD flag = ParseFromString< DWORD >( tokens[2] );

			cmd::Command* obj = g_CommandProcessor.CommandObject( realCommand );
			if ( obj )
				obj->AddCommandAlias( alias );

		}
		
		fin.close();
		return true;
	} else {
		return false;
	}
}

// This is automatically called by diablo ii whenever an outgoing chat message
// with a leading / is sent out during a game.
BOOL __fastcall ProcessChat( char *message )
{
	cmd::ProcessResult result = g_CommandProcessor.ProcessCommand( message );
	if ( result == cmd::invalidArgs )
	{
		//display( RED, "Invalid arguments specified, use /help for more info" );
		return !BNETHANDLE;

	} else if ( result == cmd::notFound ) {
		// If the command wasn't found, let battle.net take care of it
		//display( "Command not found, use /help for a list of commands", RED );
		return BNETHANDLE;

	} else if ( result == cmd::success ) {
		// Just have 'success' mean 'we've handled it'
		// and 'failed' mean 'let battle.net handle it'
		
		return !BNETHANDLE;
	}

	return BNETHANDLE;
}

namespace cmd
{
	Command* CommandProcessor::CommandObject( const std::string& command )
	{
		CommandList::iterator iter = std::find( m_commands.begin(), 
		m_commands.end(), command );

		return ( iter == m_commands.end() ? NULL : *iter );
	}

	void CommandProcessor::Initialize( const CommandProcessor::CommandList& cmdList )
	{
		m_commands = cmdList;
	}

	void CommandProcessor::Terminate()
	{
		for ( CommandList::iterator iter = m_commands.begin();
			iter < m_commands.end(); ++iter )
		{
			delete (*iter);
		}

		m_commands.resize( 0 );
	}

	ProcessResult CommandProcessor::ProcessCommand( const std::string& commandString )
	{
		// Tokenize full command string at each space
		StringTokenizer tokens( commandString, " " );
		std::string command( tokens.begin()->begin() + 1, tokens.begin()->end() );
		tokens.erase( tokens.begin() );

		// Find object which matches command
		CommandList::iterator iter = std::find( m_commands.begin(), 
			m_commands.end(), command );

		// Valid command?
		if ( iter != m_commands.end() )
		{
			// process
			return (*iter)->ProcessCommand( tokens );
		} 

		// Command or alias not found
		return notFound;
	}


}

