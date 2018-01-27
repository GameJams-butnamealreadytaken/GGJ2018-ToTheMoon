#pragma once

#if __gnu_linux__
#	include <uuid/uuid.h>
#else
#	include <rpc.h>
#endif // __gnu_linux__

#define CURRENT_NETWORK_VERSION (0xFF0002)

namespace Network
{

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
	PING					= 0x0002,

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
