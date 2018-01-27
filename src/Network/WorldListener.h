#pragma once


namespace Network
{

class Ship;
class Transmitter;

class WorldListener
{
public:

	virtual void onShipCreated(const Ship * ship) = 0;
	virtual void onTransmitterCreate(const Transmitter * ship) = 0;

};

}
