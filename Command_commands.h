#pragma once
#include "command.h"
#include "Display.h"
#include <string>
namespace cmd
{
	namespace process
	{
		//////////////////////////////
		// packetdisplay command:
		// dumps packet info onscreen
		//////////////////////////////

		class PacketDisplay : public Command
		{
		public:
			
			PacketDisplay( std::string displayByDefault = "off" ) : Command( "packetdisplay" )
			{
				g_Variables["packetdisplay"] = displayByDefault;
				display(YELLOW, "Packet displayer loaded");
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
			
			MinHealth( std::string defaultMinHealth ) : Command( "min" )
			{
				g_Variables["minhealth"] = defaultMinHealth;
				display(YELLOW, "Min-health loaded: minimum health is %s", defaultMinHealth.c_str() );
				//display(std::string(g_Variables["minhealth"]), YELLOW);
			}

		protected:
			PROCESS_FUNCTION;
		};

		//////////////////////////////
		// This is a simple class designed
		// to 
		class Test : public Command
		{
		public:
			Test ( ) : Command( "test" )
			{
				display(YELLOW, "Test-command loaded");
			}
		protected:
			PROCESS_FUNCTION;
		};

		//////////////////////////////////////
		// A command to simply add a value to the log manually
		class Log : public Command
		{
		public:
			Log() : Command( "log" )
			{
				display(YELLOW, "Logger loaded");
			}
		protected:
			PROCESS_FUNCTION;
		};
	}
}

