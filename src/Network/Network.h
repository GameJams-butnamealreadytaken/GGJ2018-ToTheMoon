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

}
