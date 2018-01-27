#pragma once

class NetworkHelper
{
public:

	NetworkHelper();
	~NetworkHelper();

	//
	// Socket management
	bool InitSocket(void);
	void CloseSocket(void);

	//
	// Broadcast to the entire network
	bool BroadcastMessage(void * msg, unsigned int size);

	template<typename T>
	bool BroadcastMessage(const T & msg)
	{
		return(BroadcastMessage((void*)&msg, sizeof(T)));
	}

	//
	// Send to all known clients
	bool SendMessageToMachine(void * msg, unsigned int size, char * machine);

	template<typename T>
	bool SendMessageToMachine(const T & msg, char * machine)
	{
		return(SendMessageToMachine((void*)&msg, sizeof(T), machine));
	}

	//
	// Receive
	bool Receive(char * buffer, unsigned int & size, char * machine, char * service);

	//
	// ...
	static bool discoverNetwork(char * szBroadcast, int iLength);

protected:


private:

	int m_sock;
};
