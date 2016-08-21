#include <Dream/network.hpp>
#include <Dream/Dream.hpp>

#include <cerrno>
#include <csignal>

void HTTP_Init();
void HttpD_Thread(thread_list*);
void GameD_Thread(thread_list*);
void BroadcastD_Thread(thread_list*);

network::network()
{
#ifdef WIN32
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2,0), &WSAData);
#else
	signal(SIGPIPE, SIG_IGN);
#endif
}

network::~network()
{
#ifdef WIN32
	WSACleanup();
#endif
}

char* network::WGet(const char* URL)
{
	SOCKET sock2, ret = 0;
	struct sockaddr_in sin;

	char *tmp, *end, hostname[256+1];
	memset(hostname, 0, 256+1);
	tmp = strstr((char*) URL, "://");
	if (!tmp) tmp = (char*)URL;
	else tmp += 3;
	end = strchr(tmp, '/');
	if (!end) end = &tmp[strlen(tmp)];
	strncpy_s(hostname, 256+1, tmp, end-tmp);

#ifdef _MSC_VER
	struct addrinfo hints, *res;
	if (getaddrinfo(hostname, "80", &hints, &res) || !res)
		return NULL;
	sin.sin_addr.s_addr = ((struct sockaddr_in *) res->ai_addr)->sin_addr.s_addr;
#else
	struct hostent *hostinfo = NULL;
	hostinfo = gethostbyname(hostname);
	if (!hostinfo)
		return NULL;
	tmp = inet_ntoa(*(struct in_addr *)hostinfo->h_addr);
	sin.sin_addr.s_addr = inet_addr(tmp);
#endif
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);

	char *buffer = NULL;
	sock2 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = 10;
	setsockopt(sock2, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
	if (sock2 >= 0) {
		if (connect(sock2, (const struct sockaddr *)&sin, sizeof(sin)) >= 0) {
			char header_f[256];
			sprintf_s(header_f, "GET %s HTTP/1.0\r\n\r\n", strlen(end) ? end : "/");
			send(sock2, header_f, strlen(header_f), 0);
			char WData[512+1];
			memset(WData, 0, 512+1);
			ret = recv(sock2, WData, 512, 0);
			if (ret > 0) {
				tmp = strstr(WData, "\r\n\r\n");
				if (!tmp) {
					tmp = strstr(WData, "\n\n");
					if (tmp) tmp += 2;
				} else tmp += 4;
				buffer = (char*) malloc(strlen(tmp)+1);
				strcpy_s(buffer, strlen(tmp)+1, tmp);
			}
		} else {
#ifdef WIN32
			DEBUG("%s (%i) :: Could not connect socket (%s - %d)\n", __FILE__, __LINE__, hostname, WSAGetLastError());
#else
			DEBUG("%s (%i) :: Could not connect socket (%s - %d)\n", __FILE__, __LINE__, hostname, errno);
#endif
		}
		CloseSocket(&sock2);
	}
	return buffer;
}

connexion_list* network::Connnect(const char* IP, ushort Port)
{
	SOCKET sock3 = -1;
	struct sockaddr_in sin;
	inet_pton(AF_INET, IP, &sin.sin_addr.s_addr);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(Port);
	sock3 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock3 >= 0) {
		if (connect(sock3, (const struct sockaddr *)&sin, sizeof(sin)) == SOCKET_ERROR) {
#ifdef WIN32
			DEBUG("%s (%i) :: Could not connect socket (%s : %i - %d)\n", __FILE__, __LINE__, IP, Port, WSAGetLastError());
#else
			DEBUG("%s (%i) :: Could not connect socket (%s : %i - %d)\n", __FILE__, __LINE__, IP, Port, errno);
#endif
			CloseSocket(&sock3);
			return NULL;
		}
	}
	return new connexion_list(sock3, PORT_TYPE_OUT);
}

int network::start()
{
	int count = 0;
	for (int i=0; i<3; i++) {
		SOCKET sock = socket(AF_INETX, SOCK_STREAM, IPPROTO_TCP);
		if (sock == INVALID_SOCKET) {
#ifdef WIN32
			DEBUG("%s (%i) :: Could not create socket (%d)\n", __FILE__, __LINE__, WSAGetLastError());
#else
			DEBUG("%s (%i) :: Could not create socket (%d)\n", __FILE__, __LINE__, errno);
#endif
			continue;
		}

		struct sockaddr_in sa;
		sa.sin_family = AF_INET;
		ushort port = 0;
		switch (i) {
			case 2 :
				port = Sharun->Settings.Net.Ports.Bridge;
				break;
			case 1 :
				port = Sharun->Settings.Net.Ports.Httpd;
				if (port == Sharun->Settings.Net.Ports.Game)
					port = 0;
				break;
			default :
				port = Sharun->Settings.Net.Ports.Game;
		}
		if (!port) {
			CloseSocket(&sock);
			continue;
		}
		sa.sin_port = htons(port);
		if (Sharun->Settings.Net.localhost)
			inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr.s_addr);
		else
			sa.sin_addr.s_addr = INADDR_ANY;

		int sockopt = 1;
		setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&sockopt, sizeof(int));

		if (bind(sock, (SOCKADDR *)&sa, sizeof(sa)) == SOCKET_ERROR) {
#ifdef WIN32
			DEBUG("%s (%i) :: Could not bind socket (%i - %d)\n", __FILE__, __LINE__, port, WSAGetLastError());
#else
			DEBUG("%s (%i) :: Could not bind socket (%i - %d)\n", __FILE__, __LINE__, port, errno);
#endif
			CloseSocket(&sock);
			continue;
		}

		if (listen(sock, 100) == SOCKET_ERROR) {
#ifdef WIN32
			DEBUG("%s (%i) :: Could not listen socket (%i - %d)\n", __FILE__, __LINE__, port, WSAGetLastError());
#else
			DEBUG("%s (%i) :: Could not listen socket (%i - %d)\n", __FILE__, __LINE__, port, errno);
#endif
			CloseSocket(&sock);
			continue;
		}

		count++;
		new connexion_list(sock, (port_type)i);
		DEBUG("%s (%i) :: Network Started (%s : %i).\n", __FILE__, __LINE__, Sharun->Settings.Net.localhost ? "localhost" : "ANY", port);
	}
	for (int i=0; count && Sharun->Settings.Thread.Httpd > 1 && i < Sharun->Settings.Thread.Httpd; i++) {
		thread_list *thread = new thread_list();
		if (!thread->start((void*)HttpD_Thread, thread))
			DEBUG("%s (%i) :: Could not start Httpd thread %i !\n", __FILE__, __LINE__, i);
		else
			DEBUG("%s (%i) :: Httpd thread %i started.\n", __FILE__, __LINE__, i);
	}
	for (int i=0; count && i < Sharun->Settings.Thread.Broadcast; i++) {
		thread_list *thread = new thread_list();
		if (!thread->start((void*)BroadcastD_Thread, thread))
			DEBUG("%s (%i) :: Could not start BroadcastD thread %i !\n", __FILE__, __LINE__, i);
		else
			DEBUG("%s (%i) :: BroadcastD thread %i started.\n", __FILE__, __LINE__, i);
	}
	for (int i=0; count && Sharun->Settings.Player_Max > 0 && i < Sharun->Settings.Player_Max; i++) {
		thread_list *thread = new thread_list();
		if (!thread->start((void*)GameD_Thread, thread))
			DEBUG("%s (%i) :: Could not start GameD thread %i !\n", __FILE__, __LINE__, i);
		else
			DEBUG("%s (%i) :: GameD thread %i started.\n", __FILE__, __LINE__, i);
	}
	HTTP_Init();
	return count;
}

void network::stop()
{
	connexions_cleanup();
	DEBUG("%s (%i) :: Network Stoped.\n", __FILE__, __LINE__);
}
