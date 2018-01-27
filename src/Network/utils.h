#pragma once

#if __gnu_linux__
#	include <uuid/uuid.h>
#endif // __gnu_linux__

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
	HELLO				= 0x001,
	SYNC_SHIP_STATE		= 0x002,
	CREATE_SHIP			= 0x003,
	CREATE_TRANSMITTER	= 0x004
};

struct HelloMessage
{
	HelloMessage()
	{
		id = HELLO;
	}

	MSG_ID id;
};

struct SyncShipStateMessage
{
	SyncShipStateMessage()
	{
		id = SYNC_SHIP_STATE;
	}

	MSG_ID id;
	uuid_t shipId;

	vec2 position;
	vec2 target;
	float speed;
};

struct CreateShipMessage
{
	CreateShipMessage()
	{
		id = CREATE_SHIP;
	}

	MSG_ID id;
	uuid_t shipId;

	vec2 position;
	vec2 target;
	float speed;
};

struct CreateTransmitterMessage
{
	CreateTransmitterMessage()
	{
		id = CREATE_TRANSMITTER;
	}

	MSG_ID id;
	unsigned int transmitterId;

	vec2 position;
};

}
