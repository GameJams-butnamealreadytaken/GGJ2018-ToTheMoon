#include "NetworkHelper.h"

#include <stdio.h> // memset

#if WIN32
#	include <winsock2.h>
#	include <ws2tcpip.h>
#	include <IPHlpApi.h>
#else
#	include <sys/socket.h>
#	include <netinet/in.h>
#	include <net/if.h>
#	include <arpa/inet.h>
#	include <netdb.h>
#	include <unistd.h>
#endif // WIN32

#include <assert.h>
#include <string.h> // memset

#define PORT (8123)

#define BRD_HELO_ADDR	"192.168.1.255"
#define BRD_HELO_PORT	(PORT)

/**
 * @brief Constructor
 */
NetworkHelper::NetworkHelper(void)
{
	m_sock = -1;
}

/**
 * @brief Destructor
 */
NetworkHelper::~NetworkHelper(void)
{
	if (m_sock != -1)
	{
		CloseSocket();
	}
}

/**
 * @brief NetworkHelper::InitSocket
 * @return
 */
bool NetworkHelper::InitSocket(void)
{
	m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (m_sock < 0)
	{
		return(false);
	}

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_port = htons(PORT);
	si.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(m_sock, (struct sockaddr*)&si, sizeof(si)) <0)
	{
		CloseSocket();
		return(false);
	}

	int enable = 1;

#if WIN32
	if (setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (const char *)&enable, sizeof(int)) < 0)
#else // WIN32
	if (setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (void*)&enable, sizeof(int)) < 0)
#endif // WIN32
	{
		CloseSocket();
		return(false);
	}

	return(true);
}

/**
 * @brief NetworkHelper::CloseSocket
 */
void NetworkHelper::CloseSocket(void)
{
#if WIN32
	closesocket(m_sock);
#else // WIN32
	close(m_sock);
#endif // WIN32

	m_sock = -1;
}

/**
 * @brief NetworkHelper::BroadcastMessage
 * @param msg
 * @param size
 * @return
 */
bool NetworkHelper::BroadcastMessage(void * msg, unsigned int size)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(BRD_HELO_PORT);
	addr.sin_addr.s_addr = inet_addr(BRD_HELO_ADDR);

#if WIN32
	/*SSIZE_T size =*/ sendto(m_sock, (const char*)msg, size, 0, (sockaddr*)&addr, sizeof(addr));
#else // WIN32
	/*ssize_t size =*/ sendto(m_sock, (void*)msg, size, 0, (sockaddr*)&addr, sizeof(addr));
#endif // WIN32

	return(true);
}

/**
 * @brief NetworkHelper::SendMessage
 * @param msg
 * @param size
 * @return
 */
bool NetworkHelper::SendMessageToMachine(void * msg, unsigned int size, char * machine)
{
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(machine);

#if WIN32
	/*SSIZE_T size =*/ sendto(m_sock, (const char*)msg, size, 0, (sockaddr*)&addr, sizeof(addr));
#else // WIN32
	/*ssize_t size =*/ sendto(m_sock, (void*)msg, size, 0, (sockaddr*)&addr, sizeof(addr));
#endif // WIN32

	return(true);
}

/**
 * @brief NetworkHelper::Receive
 * @return
 */
bool NetworkHelper::Receive(char * buffer, unsigned int & size, char * machine, char * service)
{
	fd_set fdset;
	FD_ZERO(&fdset);
	FD_SET(m_sock, &fdset);

	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;

	if (select(m_sock+1, &fdset, nullptr, nullptr, &timeout) > 0)
	{
		struct sockaddr_storage sender;
		socklen_t sendsize = sizeof(sender);
		memset(&sender, 0, sizeof(sender));

#if WIN32
		size = recvfrom(m_sock, buffer, size, 0, (struct sockaddr*)&sender, &sendsize);
#else // WIN32
		size = recvfrom(m_sock, buffer, size, 0, (struct sockaddr*)&sender, &sendsize);
#endif // WIN32

		if (machine && service)
		{
			int res = getnameinfo((struct sockaddr*)&sender, sendsize, machine, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
			assert(res == 0);
		}

		return(true);
	}

	return(false);
}

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
