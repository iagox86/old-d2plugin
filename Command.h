#pragma once
#include <windows.h>

#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue> 
#include <map>
#include <fstream>

#include "StringTokenizer.h"

#define BNETHANDLE 0
#define PROCESS_FUNCTION virtual ProcessResult ProcessCommand( const ArgList& args ) const

// List of application variables
// eg. "minhealth" =	32
//     "packetlog" =	1
//     "packetdisplay = 0
extern std::map< std::string, std::string > g_Variables;

namespace cmd
{	
	// Forward declarations
	class CommmandProcessor;
	class Command;
	// Command subclasses
	class WriteMem;
	class ReadMem;
	class PacketLog;
	class PacketDisplay;
	class MinHealth;

	// Return type for processed commands
	// basically boolean, with an invalidArgs option
	enum ProcessResult { failed, success, invalidArgs, notFound, force32BitEnum = 0x7fffffff };

	// Base class command
	// Provides an interface for commands to inherit from
	// all processing is done in operator()
	class Command
	{
	public:	
		friend class CommandProcessor;

		typedef std::vector< std::string > ArgList;
		typedef std::list< std::string > CommandStringList;

	public:
		Command( const std::string& cmd )
			: m_commandStrings( 1, cmd ) {};

		Command( const CommandStringList& cmds )
			: m_commandStrings( cmds ) {}; 
		
	public:
		inline bool operator==( const std::string& str ) const {
			return IsCommandAlias( str );
		} 
		
		void AddCommandAliases( const CommandStringList& cmds ) 
		{
			//m_commandStrings.merge( cmds );
			for ( CommandStringList::const_iterator iter = cmds.begin();
				iter != cmds.end(); ++iter )
			{
				m_commandStrings.push_back( *iter );
			}
		}

		inline void AddCommandAlias( const std::string& str ) {
			m_commandStrings.push_back( str );
		} 
		
		inline bool IsCommandAlias( const std::string& str ) const {
			CommandStringList::const_iterator iter = 
				std::find( m_commandStrings.begin(), m_commandStrings.end(), str );

			return iter != m_commandStrings.end();
		}

	protected:
		PROCESS_FUNCTION = 0;

	protected:
		CommandStringList m_commandStrings;
	};

	// Command* equality, dereferences cmd and compares it with str using
	// Command's operator ==
	__forceinline bool operator==( const Command* command, const std::string& str ) {
		return command->operator==( str );
	}

    /*
	class Alias : public Command
	{
	public:
		Alias( const std::string& command, const Command* aliasFor ) 
			: m_aliasFor( aliasFor ), Command( command ) {};

		PROCESS_FUNCTION
		{
			return m_aliasFor->operator ()( ArgList );
		}
		
	protected:
		Command* m_aliasFor;
	};
	*/

	// Manages a list of Command-derived objects
	// and passes command-strings to be processed
	class CommandProcessor
	{
	public:

		typedef std::deque< Command* > CommandList;

	public:

		//CommandProcessor( const CommandList& cmdList ) {
		//	this->Initialize( cmdList );
		//}

		~CommandProcessor() { 
			this->Terminate(); 
		}

		void Initialize( const CommandList& cmdList );
		void Terminate();
		ProcessResult ProcessCommand( const std::string& commandString );

		// Retrieve existing command object
		Command* CommandObject( const std::string& command );

	protected:

		CommandList m_commands;
	};
}

BOOL __fastcall ProcessChat( char *message );
void InitFullCommandProcessor();
bool LoadAliases( const std::string& aliasFile );
bool SyncVariables( const std::string& varFile, bool load );

// Global command processor object
extern cmd::CommandProcessor g_CommandProcessor;

