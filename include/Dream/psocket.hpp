#ifndef _PSOCKET_HPP_
#define _PSOCKET_HPP_

#ifdef WIN32
	#include <winsock2.h>
	#include <windows.h>
	#ifdef _MSC_VER
		#include <ws2tcpip.h>
	#endif
#else
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <ifaddrs.h>
	#include <netdb.h>
#endif

#ifdef IPv6
	#define AF_INETX AF_INET6
#else
	#define AF_INETX AF_INET
#endif

#endif // _PSOCKET_HPP_
