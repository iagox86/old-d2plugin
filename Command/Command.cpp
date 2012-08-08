#include "command.h"
#include "command_commands.h"

std::map< std::string, DWORD > g_Variables;
cmd::CommandProcessor g_CommandProcessor;

void InitFullCommandProcessor()
{
	cmd::CommandProcessor::CommandList commandList;
	commandList.push_back( new cmd::process::MinHealth( 25 ) );
	commandList.push_back( new cmd::process::PacketDisplay( 0 ) );
	commandList.push_back( new cmd::process::PacketLog( 1 ) );
	commandList.push_back( new cmd::process::ReadMem() );
	commandList.push_back( new cmd::process::WriteMem() );

	// add more here

	g_CommandProcessor.Initialize( commandList );
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
			DWORD flag = boost::lexical_cast< DWORD >( tokens[2] );

			cmd::Command* obj = g_CommandProcessor.CommandObject( realCommand );
			if ( obj )
				obj->AddCommandAlias( alias );

		}
		
		return true;
	} else {
		return false;
	}
}

BOOL __fastcall ProcessChat( char *message )
{
	cmd::ProcessResult result = g_CommandProcessor.ProcessCommand( message );
	if ( result == cmd::invalidArgs )
	{
		display( "Invalid arguments specified, use /help for more info", RED );
		return !BNETHANDLE;

	} else if ( result == cmd::notFound ) {

		display( "Command not found, use /help for a list of commands", RED );
		return !BNETHANDLE;

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
		// fill m_commands with Command-derived objects
		//m_commands.push_back( new ReadMem() );
		//m_commands.push_back( new WriteMem() );
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
#ifdef USE_BOOST_TOKENIZER
		boost::tokenizer<> tokens( commandString );
		std::string command = *tokens.begin();   
		cmd::Command::ArgList argumentList( tokens.end() - tokens.begin(), "" );
		std::copy( tokens.begin() + 1, tokens.end(), argumentList.begin() );
#else
		StringTokenizer tokens( commandString, " " );
		std::string command( tokens.begin()->begin() + 1, tokens.begin()->end() );
		tokens.erase( tokens.begin() );
#endif

		// Find object which matches command
		CommandList::iterator iter = std::find( m_commands.begin(), 
			m_commands.end(), command );

		// Valid command?
		if ( iter != m_commands.end() )
		{
			// process
#ifdef USE_BOOST_TOKENIZER
			return (*iter)->ProcessCommand( argumentList );
#else
			return (*iter)->ProcessCommand( tokens );
#endif
		} 

		// Command or alias not found
		return notFound;
	}

	namespace process
	{
		ProcessResult WriteMem::ProcessCommand( const Command::ArgList& args ) const
		{
			if ( args.size() < 2 )
			{
				// No arguments passed, use some default instead
				// or just return invalidArgs

				return invalidArgs;

			} else {

				DWORD addr = boost::lexical_cast< DWORD >( args[0] );
				DWORD value = boost::lexical_cast< DWORD >( args[1] );

				// FIXME:
				//BOOL result = WriteProcessMemory( ... );
				OutputDebugString( "WriteMem()\n" );

				return success;
			}
		}


		ProcessResult ReadMem::ProcessCommand( const Command::ArgList& args ) const
		{
			if ( args.size() < 2 )
			{
				return invalidArgs;

			} else {

				DWORD addr = boost::lexical_cast< DWORD >( args[0] );
				DWORD value = boost::lexical_cast< DWORD >( args[1] );

				// FIXME:
				//BOOL result = ReadProcessMemory( ... );
				OutputDebugString( "ReadMem()\n" );

				return success;
			}
		}

		ProcessResult PacketLog::ProcessCommand( const Command::ArgList& args )	const
		{
			if ( args.size() == 0 )
			{
				// User didn't specify on or off, toggle it
				return invalidArgs;

			} else {

				if ( args[0] == "on" )
				{
					g_Variables["packetlog"] = 1;
					// turn on packet logging

				} else if ( args[0] == "off" ) {

					g_Variables["packetlog"] = 0;
					// turn off packet logging

				} else {

					// "on" or "off" not specified
					return invalidArgs;
				}
			}

			return success;
		}

		ProcessResult PacketDisplay::ProcessCommand( const Command::ArgList& args )	const
		{
			if ( args.size() == 0 )
			{
				// User didn't specify on or off, toggle it
				return invalidArgs;

			} else {

				if ( args[0] == "on" )
				{
					g_Variables["packetdisplay"] = 1;
					// turn on packet logging

				} else if ( args[0] == "off" ) {

					g_Variables["packetdisplay"] = 0;
					// turn off packet logging

				} else {

					// "on" or "off" not specified
					return invalidArgs;
				}
			}

			return success;
		}

		ProcessResult MinHealth::ProcessCommand( const Command::ArgList& args ) const
		{
			if ( args.size() == 0 )
			{
				return invalidArgs;

			} else {

				g_Variables["minhealth"] = boost::lexical_cast< DWORD >( args[0] );
				// set new minimum health
			}

			return success;
		}
	}
}

