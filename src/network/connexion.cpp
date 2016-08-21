#include <Dream/network.hpp>
#include <Dream/Dream.hpp>
#include "httpd_link.hpp"

#include <cstring>
#include <cerrno>
//#include <unistd.h>

void CloseSocket(SOCKET *sock)
{
	if (*sock >= 0) {
#ifdef WIN32
		closesocket(*sock);
#else
		shutdown(*sock, SHUT_RDWR);
		close(*sock);
#endif
	}
	*sock = INVALID_SOCKET;
}

void HttpD(connexion_list*);
void GameD(connexion_list*);
void GameD_Add(player*);

connexion_list* connexions = NULL;
connexion_list* connexions_last = NULL;
pthread_mutex_t connexions_mtx;
bool connexions_mtx_init = false;

void connexions_cleanup()
{
	if (connexions_mtx_init) {
		pthread_mutex_lock(&connexions_mtx);
		connexion_list* t_connex = NULL;
		while (connexions) {
			t_connex = connexions;
			connexions = connexions->next;
			pthread_mutex_unlock(&connexions_mtx);
			delete t_connex;
			pthread_mutex_lock(&connexions_mtx);
		}
		pthread_mutex_unlock(&connexions_mtx);
		pthread_mutex_destroy(&connexions_mtx);
	}
	connexions_mtx_init = false;
}

connexion_list::connexion_list(SOCKET in, port_type p_t_t)
{
	if (!connexions_mtx_init) {
		connexions_mtx_init = true;
		pthread_mutex_init(&connexions_mtx, NULL);
	}
	p_t = p_t_t;
	sock = in;
	next = NULL;
	prev = NULL;
	new_crypt = 0;
	teraCrypt = NULL;
	teraCrypt_Client = false;
	mother = NULL;
	Player = NULL;
	pthread_mutex_init(&teraCrypt_Mtx_S, NULL);
	pthread_mutex_init(&teraCrypt_Mtx_R, NULL);
	pthread_mutex_lock(&connexions_mtx);
	if (!connexions)
		connexions = connexions_last = this;
	else {
		connexions_last->next = this;
		prev = connexions_last;
		connexions_last = this;
	}
	pthread_mutex_unlock(&connexions_mtx);
	thread_list *thread;
	
	switch ((short) p_t) {
		case PORT_TYPE_IN_HTTPD:
			mother = thread = new thread_list();
			if (!thread->start((void*)HttpD, this)) {
				delete thread;
				delete this;
			}
			break;
		case PORT_TYPE_IN_GAME:
			mother = thread = new thread_list();
			if (!thread->start((void*)GameD, this)) {
				delete thread;
				delete this;
			}
			break;
	}
}

connexion_list::~connexion_list()
{
	Set_timeout(1);
	CloseSocket(&sock);
	pthread_mutex_destroy(&teraCrypt_Mtx_S);
	pthread_mutex_destroy(&teraCrypt_Mtx_R);
	if (teraCrypt) {
		Crypt::Session *Sess = (Crypt::Session *)teraCrypt;
		delete Sess;
		teraCrypt = NULL;
	}
	if (Player)
		Player->connex = NULL;
	Player = NULL;
	pthread_mutex_lock(&connexions_mtx);
	if (prev)
		prev->next = next;
	else
		connexions = next;
	if (next)
		next->prev = prev;
	pthread_mutex_unlock(&connexions_mtx);
}

void connexion_list::Key(const char *keys, bool i_m_server)
{
	if (teraCrypt) {
		Crypt::Session *Sess = (Crypt::Session *)teraCrypt;
		delete Sess;
		teraCrypt = NULL;
		new_crypt++;
	}
	teraCrypt_Client = i_m_server;
	if (!teraCrypt_Client)
		teraCrypt = new Crypt::Session(&keys[0*128], &keys[1*128], &keys[2*128], &keys[3*128], new_crypt);
	else
		teraCrypt = new Crypt::Session(&keys[2*128], &keys[3*128], &keys[0*128], &keys[1*128], new_crypt);
}

void connexion_list::Encode(byte* raw, ushort size)
{
	if (!teraCrypt)
		return;
	Crypt::Session *Sess = (Crypt::Session *)teraCrypt;
	if (!teraCrypt_Client)
		Sess->Encrypt(raw, size);
	else
		Sess->Decrypt(raw, size);
}

void connexion_list::Decode(packet *packet_l, bool head)
{
	if (!teraCrypt)
		return;
	Crypt::Session *Sess = (Crypt::Session *)teraCrypt;
	if (!teraCrypt_Client)
		Sess->Decrypt(packet_l->raw + (head ? 0 : 4), (head ? 4: packet_l->size - 4));
	else
		Sess->Encrypt(packet_l->raw + (head ? 0 : 4), (head ? 4: packet_l->size - 4));
}

void connexion_list::Decode_Direct(byte* raw, ushort size)
{
	if (!teraCrypt)
		return;
	Crypt::Session *Sess = (Crypt::Session *)teraCrypt;
	if (!teraCrypt_Client)
		Sess->Decrypt(raw, size);
	else
		Sess->Encrypt(raw, size);
}

void connexion_list::Set_timeout(ushort sec)
{
	struct timeval tv;
	tv.tv_usec = 0;
	tv.tv_sec = sec;
	setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));
}

int connexion_list::Send_Direct(char* raw, ushort size)
{
	pthread_mutex_lock(&teraCrypt_Mtx_S);
	hexdump("player::Send_Direct", "???", raw, size);
	Encode((byte*) raw, size);
	int ret = Send(raw, size);
	if (ret == SOCKET_ERROR || ret == 0) {
		CloseSocket(&sock);
		ret = -1;
	}
	if (sock != INVALID_SOCKET)
		pthread_mutex_unlock(&teraCrypt_Mtx_S);
	delete raw;
	return ret;
}

int connexion_list::Send(packet *packet_l)
{
	pthread_mutex_lock(&teraCrypt_Mtx_S);
const char * fcn_name = Sharun->OpCodes.Send_name(packet_l);
if ( strcmp(fcn_name, "S_SIMPLE_TIP_REPEAT_CHECK")
  && strcmp(fcn_name, "S_RESPONSE_GAMESTAT_PONG") )
	hexdump("player::send", fcn_name, packet_l->raw, packet_l->size);
	Encode(packet_l->raw, packet_l->size);
	int ret = Send((char*)packet_l->raw, packet_l->size);
	if (ret == SOCKET_ERROR || ret == 0) {
		CloseSocket(&sock);
		ret = -1;
	}
	if (sock != INVALID_SOCKET)
		pthread_mutex_unlock(&teraCrypt_Mtx_S);
	delete packet_l;
	return ret;
}

int connexion_list::Send(const char *data, int len)
{
	if (sock == INVALID_SOCKET)
		return -1;
	int ret = send(sock, data, len, 0);
	if (ret == SOCKET_ERROR || ret == 0) {
		CloseSocket(&sock);
		ret = -1;
	}
	return ret;
}

int connexion_list::Send(const char *data)
{
	return Send(data, strlen(data));
}

int connexion_list::Recv(packet *packet_l)
{
	pthread_mutex_lock(&teraCrypt_Mtx_R);
	int len, ret;
	ret = Recv((char*)packet_l->raw, 4);
	if (ret == SOCKET_ERROR || ret == 0) {
		CloseSocket(&sock);
		ret = -1;
		pthread_mutex_unlock(&teraCrypt_Mtx_R);
		return -1;
	}
	len = ret;
	if (sock == INVALID_SOCKET)
		return -1;
	Decode(packet_l, true);
	packet_l->get_header();
	while (packet_l->size > len && sock != INVALID_SOCKET && ret >= 0) {
		ret = Recv((char*)&packet_l->raw[len], packet_l->size - len);
		if (ret == SOCKET_ERROR) {
			if (sock != INVALID_SOCKET)
				pthread_mutex_unlock(&teraCrypt_Mtx_R);
			CloseSocket(&sock);
			return -1;
		}
		len += ret;
	}
	if (sock == INVALID_SOCKET)
		return -1;
	Decode(packet_l, false);
	if (sock != INVALID_SOCKET)
		pthread_mutex_unlock(&teraCrypt_Mtx_R);
	return len;
}

int connexion_list::Recv(char *data, int len)
{
	if (sock == INVALID_SOCKET)
		return -1;
	int ret = recv(sock, data, len, 0);
	if (ret == SOCKET_ERROR || ret == 0) {
		CloseSocket(&sock);
		ret = -1;
	}
	return ret;
}

int connexion_list::Recv(char *data, int *len)
{
	*len = Recv(data, *len);
	return *len;
}

void HttpD(connexion_list *connex)
{
	thread_list *thread = (thread_list*)connex->mother;
	while (connex->sock != INVALID_SOCKET) {
		struct sockaddr_in csin = { 0 };
		socklen_t csin_s = sizeof(csin);
		SOCKET csock = accept(connex->sock, (struct sockaddr *)&csin, &csin_s);
		if(csock == INVALID_SOCKET) {
			if (connex->sock != INVALID_SOCKET)
#ifdef WIN32
				DEBUG("%s (%i) :: Client (HttpD) connexion Error (%d %d)\n", __func__, __LINE__, WSAGetLastError(), csock);
#else
				DEBUG("%s (%i) :: Client (HttpD) connexion Error (%d %d)\n", __func__, __LINE__, errno, csock);
#endif
		} else {
			httpd_link_t *httpd_link = new httpd_link_t;
			httpd_link->noHead = false;
			httpd_link->connex = new connexion_list(csock, PORT_TYPE_OUT);
			httpd_link->Size = httpd_link->connex->Recv(httpd_link->Head, httpd_link_Head_Size);
			if (Sharun->Settings.Thread.Httpd > 1)
				HttpD_Add(httpd_link);
			else
				HTTP_Work(httpd_link);
		}
	}
	thread->internal_delete();
	DEBUG("%s (%i) :: Network HttpD Stopped (%s).\n", __FILE__, __LINE__, Sharun->Settings.Net.localhost ? "localhost" : "ANY");
	pthread_exit(NULL);
}

void GameD(connexion_list *connex)
{
	thread_list *thread = (thread_list*)connex->mother;
	while (connex->sock != INVALID_SOCKET) {
		struct sockaddr_in csin = { 0 };
		socklen_t csin_s = sizeof(csin);
		SOCKET csock = accept(connex->sock, (struct sockaddr *)&csin, &csin_s);
		if(csock == INVALID_SOCKET) {
			if (connex->sock != INVALID_SOCKET)
#ifdef WIN32
				DEBUG("%s (%i) :: Client (GameD) connexion Error (%d %d)\n", __func__, __LINE__, WSAGetLastError(), csock);
#else
				DEBUG("%s (%i) :: Client (GameD) connexion Error (%d %d)\n", __func__, __LINE__, errno, csock);
#endif
		} else {
			httpd_link_t *httpd_link = NULL;
			connexion_list *connex_t = new connexion_list(csock, PORT_TYPE_OUT);
//DEBUG("%s (%i) :: Someone connected\n", __func__, __LINE__);
			if (Sharun->Settings.Net.Ports.Game == Sharun->Settings.Net.Ports.Httpd) {

//DEBUG("%s (%i) :: Detect a browser...\n", __func__, __LINE__);
				httpd_link = new httpd_link_t;
				httpd_link->noHead = false;
				httpd_link->connex = connex_t;
				connex_t->Set_timeout(2);
				httpd_link->Size = httpd_link->connex->Recv(httpd_link->Head, httpd_link_Head_Size);
				connex_t->Set_timeout(0);
				if (httpd_link->Size > 0) {
					if (Sharun->Settings.Thread.Httpd > 1)
						HttpD_Add(httpd_link);
					else
						HTTP_Work(httpd_link);
					continue;
				}
			}
			if (httpd_link)
				delete httpd_link;
			char tmpIP[16];
			inet_ntop(AF_INET, &csin.sin_addr.s_addr, tmpIP, 16);
			strcpy_s(connex_t->IP, 16, tmpIP);
//DEBUG("%s (%i) :: Request Key\n", __func__, __LINE__);
			int conn_ok = 1;
			connex_t->Send((char*) &conn_ok, 4);
			char *Key_l = new char[4*128];
			for (int i=0; i<2; i++)
				for (int j=0; j<128; j++)
					Key_l[(2+i)*128+j] = rand() % 0xff;
			bool rrun = true;
			for (int i=0; i<2 && rrun; i++) {
				int ret = connex_t->Recv(&Key_l[(0+i)*128], 128);
//	hexdump(__func__, "Client Key", &Key_l[(0+i)*128], 128);
				if (ret != 128) {
					DEBUG("%s (%i) :: Client Key %i ! (%i<128)\n", __func__, __LINE__, i+1, ret);
					rrun = false;
					delete connex_t;
					delete Key_l;
					continue;
				}
				if (rrun) {
					ret = connex_t->Send(&Key_l[(2+i)*128], 128);
//	hexdump(__func__, "Server Key", &Key_l[(2+i)*128], 128);
				}
			if (rrun  && ret != 128) {
					DEBUG("%s (%i) :: Server Key %i ! (%i<128)\n", __func__, __LINE__, i+1, ret);
					rrun = false;
					delete connex_t;
					delete Key_l;
					continue;
				}
			}
			byte *C_C_VERS1 = NULL, *C_C_VERS2 = NULL;
			if (rrun) {
				connex_t->Key(Key_l, false);
				C_C_VERS1 = new byte[32];
				C_C_VERS2 = new byte[32];
//DEBUG("%s (%i) :: Wait Version\n", __func__, __LINE__);
				connex_t->Recv((char*) C_C_VERS1, 32);
				do {
					memcpy(C_C_VERS2, C_C_VERS1, 32);
					connex_t->Decode_Direct(C_C_VERS2, 32);
					if ( C_C_VERS2[ 0] == 0x20
					  && C_C_VERS2[ 1] == 0x00
					  && C_C_VERS2[ 2] == 0xBC
					  && C_C_VERS2[ 3] == 0x4D
					  && C_C_VERS2[ 4] == 0x02
					  && C_C_VERS2[ 5] == 0x00
					  && C_C_VERS2[ 6] == 0x08
					  && C_C_VERS2[ 7] == 0x00
					  && C_C_VERS2[ 8] == 0x08
					  && C_C_VERS2[ 9] == 0x00
					  && C_C_VERS2[10] == 0x14
					  && C_C_VERS2[11] == 0x00
					  && C_C_VERS2[12] == 0x00
					  && C_C_VERS2[13] == 0x00
					  && C_C_VERS2[14] == 0x00
					  && C_C_VERS2[15] == 0x00
					  && C_C_VERS2[20] == 0x14
					  && C_C_VERS2[21] == 0x00
					  && C_C_VERS2[22] == 0x00
					  && C_C_VERS2[23] == 0x00
					  && C_C_VERS2[24] == 0x01
					  && C_C_VERS2[25] == 0x00
					  && C_C_VERS2[26] == 0x00
					  && C_C_VERS2[27] == 0x00 ) {
						delete C_C_VERS1;
						C_C_VERS1 = NULL;
					}
					else
						connex_t->Key(Key_l, false);
				} while (C_C_VERS1 && connex_t->new_crypt < get_teraCrypt_version());
			}
			delete Key_l;
			delete C_C_VERS2;
			packet* packet_l = NULL;
			if (C_C_VERS1) {
				DEBUG("%s (%i) :: Can't dencrypt client ! (%i >= %i)\n", __func__, __LINE__, connex_t->new_crypt, get_teraCrypt_version());
				delete C_C_VERS1;
				delete connex_t;
			} else 
				packet_l = new packet(0);
//DEBUG("%s (%i) :: Wait login data\n", __func__, __LINE__);
			player* player_l = new player(connex_t);
			if (packet_l) {
				player_l->connex->Recv(packet_l);
				player_l->Op_GID = Sharun->OpCodes.Get_GID(packet_l);
				player_l->Client_Version = Sharun->OpCodes.list[player_l->Op_GID].version;
			}
			packet* packet_V = new_packet(S_CHECK_VERSION, 1);
			if (!packet_l || player_l->Op_GID < 0) {
				packet_V->write_1(0);
				player_l->Send(packet_V);
				delete player_l;
			} else {
				packet_V->write_1(1);
				player_l->Send(packet_V);
				player_l = (player*)Sharun->OpCodes.Recv(player_l, packet_l);
				if (player_l)
					GameD_Add(player_l);
			}
			delete packet_l;
		}
	}
	thread->internal_delete();
	DEBUG("%s (%i) :: Network GameD Stopped (%s).\n", __FILE__, __LINE__, Sharun->Settings.Net.localhost ? "localhost" : "ANY");
	pthread_exit(NULL);
}
