#pragma once

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
	HELLO		= 0x001,
	SHIP_STATE	= 0x002
};

struct HelloMessage
{
	HelloMessage()
	{
		id = HELLO;
	}

	MSG_ID id;
};

struct ShipStateMessage
{
	ShipStateMessage()
	{
		id = SHIP_STATE;
	}

	MSG_ID id;
	unsigned int shipId;

	vec2 position;
	vec2 target;
	float speed;
};


}
