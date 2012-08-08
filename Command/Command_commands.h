#pragma once
#include "command.h"

namespace cmd
{
	namespace process
	{
		//////////////////////////////
		// writemem command:
		// writes process memory and
		// displays results onscreen
		//////////////////////////////
		class WriteMem : public Command
		{
		public:
			WriteMem() : Command( "writemem" ) {
				m_hProcess = GetCurrentProcess( );
			}

		protected:
			PROCESS_FUNCTION;

		protected:
			HANDLE m_hProcess;
		};


		//////////////////////////////
		// readmem command:
		// reads process memory and
		// displays results onscreen
		//////////////////////////////
		class ReadMem : public Command
		{
		public:
			ReadMem() : Command( "readmem" ) {
				m_hProcess = GetCurrentProcess( );
			}

		protected:
			PROCESS_FUNCTION;

		protected:
			HANDLE m_hProcess;
		};


		//////////////////////////////
		// packetlogging command:
		// logs packet info to file
		//////////////////////////////
		class PacketLog : public Command
		{
		public:
			PacketLog( DWORD logByDefault = 0 ) : Command( "packetlog" ) 
			{
				g_Variables["packetlog"] = logByDefault;
			};

		protected:
			PROCESS_FUNCTION;
		};

		//////////////////////////////
		// packetdisplay command:
		// dumps packet info onscreen
		//////////////////////////////

		class PacketDisplay : public Command
		{
		public:
			
			PacketDisplay( DWORD displayByDefault = 0 ) : Command( "packetdisplay" )
			{
				g_Variables["packetdisplay"] = displayByDefault;
			};

		protected:
			PROCESS_FUNCTION;
		};

		//////////////////////////////
		// minhealth command:
		// sets minimum health with 
		// which to bail out on
		//////////////////////////////
		class MinHealth : public Command
		{
		public:
			
			MinHealth( DWORD defaultMinHealth ) : Command( "minhealth" )
			{
				g_Variables["minhealth"] = defaultMinHealth;
			}

		protected:
			PROCESS_FUNCTION;
		};
	}
}

