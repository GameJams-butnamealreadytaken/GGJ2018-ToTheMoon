#pragma once

#if __gnu_linux__
#	include <uuid/uuid.h>
#else
#	define _WINSOCKAPI_ 
#include <stdio.h>
#	include <rpc.h>
#endif // __gnu_linux__

#define CURRENT_NETWORK_VERSION (0xFF0002)

namespace Network
{

#if WIN32
inline int NETWORK_DEBUG_LOG(const char* format, ...)
{
	static char s_printf_buf[1024];
	va_list args;
	va_start(args, format);
	_vsnprintf(s_printf_buf, sizeof(s_printf_buf), format, args);
	va_end(args);
	OutputDebugStringA(s_printf_buf);
	return 0;
}
#else
#define NETWORK_DEBUG_LOG printf
#endif // WIN32

struct vec2
{
	vec2(void)
	{
		x = 0.0f;
		y = 0.0f;
	}

	vec2(float x_, float y_)
	{
		x = x_;
		y = y_;
	}

	float x;
	float y;
};

enum MSG_ID
{
	// Service messages
	HELLO					= 0x0001,
	WELCOME					= 0x0002,
	PING					= 0x0003,

	// Ship messages
	SHIP_CREATE				= 0x0011,
	SHIP_DESTROY			= 0x0012,
	SHIP_SYNC_STATE			= 0x0013,

	// Transmitter messages
	TRANSMITTER_CREATE		= 0x0101,
	TRANSMITTER_DESTROY		= 0x0102,
	TRANSMITTER_SYNC_STATE	= 0x0103,
};

struct HelloMessage
{
	HelloMessage()
	{
		id = HELLO;
		version = CURRENT_NETWORK_VERSION;
	}

	MSG_ID id;
	uuid_t helloId;

	unsigned int version;
};

struct WelcomeMessage
{
	WelcomeMessage()
	{
		id = WELCOME;
	}

	MSG_ID id;
};


struct PingMessage
{
	PingMessage()
	{
		id = PING;
	}

	MSG_ID id;
};

struct CreateShipMessage
{
	CreateShipMessage()
	{
		id = SHIP_CREATE;
	}

	MSG_ID id;
	uuid_t shipId;

	vec2 position;
	vec2 target;
	float speed;
	unsigned int team;
};

struct DestroyShipMessage
{
	DestroyShipMessage()
	{
		id = SHIP_DESTROY;
	}

	MSG_ID id;
	uuid_t shipId;
};

struct SyncShipStateMessage
{
	SyncShipStateMessage()
	{
		id = SHIP_SYNC_STATE;
	}

	MSG_ID id;
	uuid_t shipId;

	vec2 position;
	vec2 target;
	float speed;
	unsigned int team;
};

struct CreateTransmitterMessage
{
	CreateTransmitterMessage()
	{
		id = TRANSMITTER_CREATE;
	}

	MSG_ID id;
	uuid_t transmitterId;

	vec2 position;
	unsigned int team;
};

struct DestroyTransmitterMessage
{
	DestroyTransmitterMessage()
	{
		id = TRANSMITTER_DESTROY;
	}

	MSG_ID id;
	uuid_t transmitterId;
};

struct SyncTransmitterStateMessage
{
	SyncTransmitterStateMessage()
	{
		id = TRANSMITTER_SYNC_STATE;
	}

	MSG_ID id;
	uuid_t transmitterId;

	vec2 position;
	unsigned int team;
};

}
