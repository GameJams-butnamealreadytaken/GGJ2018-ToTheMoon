#pragma once


namespace Network
{

class Ship;
class Transmitter;

class WorldListener
{
public:

	virtual void onShipCreated(const Ship * ship) = 0;
	virtual void onShipDestroyed(const Ship * ship) = 0;
	virtual void onShipStateChanged(const Ship * ship) = 0;

	virtual void onTransmitterCreated(const Transmitter * transmitter) = 0;
	virtual void onTransmitterDestroyed(const Transmitter * transmitter) = 0;
	virtual void onTransmitterStateChanged(const Transmitter * transmitter) = 0;

};

}
