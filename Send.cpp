#include "Send.h"
#include "Display.h"
#include "Command.h"
#include "Buffer.h"
#include "Logger.h"
#include "Constants.h"

// In-game packet codes
#define WALK			(BYTE) 0x03
#define WALKTO			(BYTE) 0x04
#define ATTACK			(BYTE) 0x06
#define UNKNOWN_COMBAT	(BYTE) 0x09
#define RIGHT_SPELL		(BYTE) 0x0C
#define NPCTALK_1		(BYTE) 0x13
#define GAMECHAT		(BYTE) 0x15
#define PICKUP_INV		(BYTE) 0x16
#define PICKUP_HAND		(BYTE) 0x17
#define MOVE_TO_BUFFER	(BYTE) 0x18
#define INV_TO_CURSOR	(BYTE) 0x19
#define CURSOR_TO_BODY	(BYTE) 0x1A
#define BODY_TO_CURSOR	(BYTE) 0x1C
#define NPCTALK_2		(BYTE) 0x2F
#define CLOSE_NPCTALK	(BYTE) 0x30
#define BUY_FROM_STORE	(BYTE) 0x32
#define REQUEST_BUY		(BYTE) 0x38
#define CHANGE_SKILL	(BYTE) 0x3C
#define ENTITY_WALK		(BYTE) 0x59
#define LEAVE			(BYTE) 0x68
#define KEEPALIVE		(BYTE) 0x6C

SOCKET d2Socket;

DWORD lastItemGrabbed = 0;

// This hooks D2's sendData function.  It can be used for packet logging, filtering,
// displaying, etc.
int sendData(SOCKET s, const char *buf, int length, int flags)
{
	BOOL sendOut = true;
	// Get a buffer of the send data
	Buffer b((const BYTE *)buf, length);

	// Save the socket
	d2Socket = s;

	// Packet displayer, unfiltered so far

	bool displayThis = true;

	char packet[128];
	// Remove the packet code
	BYTE code;
	b.RemoveFromFront(&code, 1);
	switch(*buf)
	{
	case WALK:
		{
			WORD x;
			WORD y;
			b >> x >> y;
			sprintf(packet, "Walking: (%04x, %04x)", x, y);

			displayThis = false;
		}
		break;

	case WALKTO:
		{
			DWORD entityType;
			DWORD entityCode;
			b >> entityType >> entityCode;
			sprintf(packet, "Walking to: %08x, type %08x", entityCode, entityType);

			displayThis = false;
		}
		break;

	case LEAVE:
		{
			sprintf(packet, "Leaving the game");

			displayThis = false;
		}
		break;

	case ATTACK:
		{
			DWORD entityType;
			DWORD entityCode;
			b >> entityType >> entityCode;
			sprintf(packet, "Attacking %08x, type %08x", entityCode, entityType);

			displayThis = false;
		}

		break;

	case KEEPALIVE:
		{
			displayThis = false;
		}

	default:
		{
			sprintf(packet, "Unknown packet: 0x%02x\n%s", code, b.toString().c_str());
			displayThis = true;
		}

	if(g_Variables["packetdisplay"] == "on")
		display(GREEN, packet);

	mylog.add(packet);
	

			

	}

	// Test function for displaying over entities
	if(sendOut)
		return send(s, buf, length, flags);
	else
		return length;
}

void leaveGame()
{
	char leave = LEAVE;

	send(d2Socket, &leave, 1, 0);
}







#include "Command_commands.h"
#include "Command.h"

namespace cmd
{
	namespace process
	{	
		ProcessResult PacketDisplay::ProcessCommand( const Command::ArgList& args )	const
		{
			if ( args.size() == 0 )
			{
				// User didn't specify on or off, toggle it
				std::string disp = g_Variables["packetdisplay"];
				if(disp == "on")
					g_Variables["packetdisplay"] = "off";
				else
					g_Variables["packetdisplay"] = "on";

			} 
			else 
			{
				if ( args[0] == "on" || args[0] == "off" )
				{
					g_Variables["packetdisplay"] = args[0];
				} 
				else 
				{

					// "on" or "off" not specified
					display(RED, "Correct usage is, \"/packetdisplay [on|off]\"");
					return invalidArgs;
				}
			}

			// Print out a message for the user
			display(GREEN, "Packets will %s be displayed.", (g_Variables["packetdisplay"] == "on") ? "now" : "no longer");

			return success;
		}
	}
}

