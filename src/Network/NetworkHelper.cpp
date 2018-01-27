#include "NetworkHelper.h"

#include <stdio.h> // memset

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
		//while (pCurrAddresses) 
		//{
			pUnicast = pCurrAddresses->FirstUnicastAddress;
			if (pUnicast != NULL)
			{
				//for (i = 0; pUnicast != NULL; i++)
				//{
					if (pUnicast->Address.lpSockaddr->sa_family == AF_INET)
					{
						char szIp[256];
						sockaddr_in *sa_in = (sockaddr_in *)pUnicast->Address.lpSockaddr;
						memset(szIp, 0, 256);
						inet_ntop(AF_INET,&(sa_in->sin_addr), szIp, 256);

						UINT8 iSubnetMask = pUnicast->OnLinkPrefixLength;
						ULONG bits = 0xffffffff ^ (1 << 32 - iSubnetMask) - 1;
						char szSubnetMask[256];
						sprintf(szSubnetMask, "%d.%d.%d.%d", (bits & 0x0000000000ff000000L) >> 24, (bits & 0x0000000000ff0000) >> 16, (bits & 0x0000000000ff00) >> 8, bits & 0xff);
						struct in_addr ip, mask, broadcast;
						inet_pton(AF_INET, szSubnetMask, &mask);
						inet_pton(AF_INET, szIp, &ip);
						broadcast.s_addr = ip.s_addr | ~mask.s_addr;
						inet_ntop(AF_INET, &broadcast, szBroadcast, iLength);
					}
				
				//	pUnicast = pUnicast->Next;
				//}
			}
		//	pCurrAddresses = pCurrAddresses->Next;
		//}
	}

	if (pAddresses) 
	{
		HeapFree(GetProcessHeap(), 0, pAddresses);
		pAddresses = NULL;
	}

	return(strcmp(szBroadcast, "") > 0);
#else // WIN32
	int sock = socket(AF_INET, SOCK_DGRAM, 0);

	
    struct ifreq *ifreq;
    struct ifconf ifconf;
    char buf[16384];
    unsigned i;
    size_t len;
 
    ifconf.ifc_len = sizeof(buf);
    ifconf.ifc_buf = buf;

    if (ioctl(sock, SIOCGIFCONF, &ifconf) != 0)
    {
        perror("ioctl(SIOCGIFCONF)");
		return(false);
    }
 
    printf("Listing all interfaces:\n");
    ifreq = ifconf.ifc_req;
    i = 0;
    //while (i < ifconf.ifc_len)
    //{
#ifndef linux
        len = IFNAMSIZ + ifreq->ifr_addr.sa_len;
#else
        len = sizeof(struct ifreq);
#endif

        printf("%s\n", ifreq->ifr_name);

        ifreq = (struct ifreq*)((char*)ifreq + len);

        i += len;
	//}

    int family;
    struct ifreq ifreq;

    if(ioctl(sock, SIOCGIFBRDADDR, &ifreq) != 0)
    {
        fprintf(stderr, "Could not find interface named %s", name);
        return; /* ignore */
    }

    getnameinfo(&ifreq.ifr_broadaddr, sizeof(ifreq.ifr_broadaddr), szBroadcast, iLength, 0, 0, NI_NUMERICHOST);
	printf("%-24s%s\n", name, host);
	
	close(sock);

	return(true);
#endif // WIN32
}