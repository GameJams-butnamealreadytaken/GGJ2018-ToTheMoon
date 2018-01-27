#include "NetworkHelper.h"

#if WIN32
#	include <ws2tcpip.h>
#	include <IPHlpApi.h>
#else // WIN32
#endif // WIN32

#include <string.h> // memset

/**
 * @brief discoverNetwork
 * @return
 */
/*static*/ bool NetworkHelper::discoverNetwork(char * szBroadcast, int iLength)
{
	memset(szBroadcast, 0, iLength);
#if WIN32
	// Declare and initialize variables
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	unsigned int i = 0;

	// Set the flags to pass to GetAdaptersAddresses
	ULONG flags = GAA_FLAG_INCLUDE_PREFIX;

	// default to unspecified address family (both)
	ULONG family = AF_UNSPEC;

	LPVOID lpMsgBuf = NULL;

	PIP_ADAPTER_ADDRESSES pAddresses = NULL;
	ULONG outBufLen = 0;
	ULONG Iterations = 0;
	
	PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
	PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
	PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
	PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
	IP_ADAPTER_DNS_SERVER_ADDRESS *pDnServer = NULL;
	IP_ADAPTER_PREFIX *pPrefix = NULL;
	family = AF_INET;
	outBufLen = 15000;
	const int MAX_TRIES = 3;
	do
	{
		pAddresses = (IP_ADAPTER_ADDRESSES *) HeapAlloc(GetProcessHeap(), 0, (outBufLen));
		if (pAddresses == NULL)
		{
			return(false);
		}

		dwRetVal = GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);

		if (dwRetVal == ERROR_BUFFER_OVERFLOW)
		{
			HeapFree(GetProcessHeap(), 0, (pAddresses));
			pAddresses = NULL;
		} 
		else
		{
			break;
		}

		Iterations++;

	} while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (Iterations < MAX_TRIES));

	if (dwRetVal == NO_ERROR)
	{
		// If successful, output some information from the data we received
		pCurrAddresses = pAddresses;
		while (pCurrAddresses) 
		{
			pUnicast = pCurrAddresses->FirstUnicastAddress;
			if (pUnicast != NULL)
			{
				for (i = 0; pUnicast != NULL; i++)
				{
					if (pUnicast->Address.lpSockaddr->sa_family == AF_INET)
					{
						sockaddr_in *sa_in = (sockaddr_in *)pUnicast->Address.lpSockaddr;
						memset(szBroadcast, 0, iLength);
						inet_ntop(AF_INET,&(sa_in->sin_addr), szBroadcast, iLength);
					}
					pUnicast = pUnicast->Next;
				}
			}
			pCurrAddresses = pCurrAddresses->Next;
		}
	}

	if (pAddresses) 
	{
		HeapFree(GetProcessHeap(), 0, pAddresses);
		pAddresses = NULL;
	}

	return(strcmp(szBroadcast, "") > 0);
#else // WIN32
	return(false);
#endif // WIN32
}