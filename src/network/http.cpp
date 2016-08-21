#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <Dream/psocket.hpp>
#include <Dream/Dream.hpp>

#include "httpd_link.hpp"
#include "mime_type.hpp"
#include "can_transform.hpp"

#include <cstdarg>
#include <sys/stat.h>
#include <limits.h>

short N_IP[2];
char NET_IP[2][16];

static const char wday_name[][4] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};
static const char mon_name[][4] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

long write_head_printf(connexion_list *connex, const char *__msg, ...)
{
	char tmp[1024];
	va_list __local_argv;
	va_start(__local_argv, __msg );
	vsprintf_s(tmp, 1024, __msg, __local_argv );
	va_end(__local_argv );
	return connex->Send(tmp);
}

void HTTP_DateTime_Char(connexion_list *connex, bool transformed, const char *file)
{
	struct stat st;
	time_t rawtime;
#ifdef _MSC_VER
 	struct tm t_info;
#else
 	struct tm* t_info;
#endif
 	char buffer [80];

	stat(file, &st);
#ifdef _MSC_VER
	localtime_s(&t_info, &st.st_ctime);
	strftime (buffer, 80, "Date:    , %d     %Y %H:%M:%S %Z\r\n", &t_info);
	strncpy_s(buffer+2+4, 80-2-4, wday_name[t_info.tm_wday], 3);
	strncpy_s(buffer+10+4, 80-10-4, mon_name[t_info.tm_mon], 3);
#else
	t_info = localtime(&st.st_ctime);
	strftime (buffer, 80, "Date:    , %d     %Y %H:%M:%S %Z\r\n", t_info);
	strncpy_s(buffer+2+4, 80-2-4, wday_name[t_info->tm_wday], 3);
	strncpy_s(buffer+10+4, 80-10-4, mon_name[t_info->tm_mon], 3);
#endif
	connex->Send(buffer);

  	if (transformed) {
		time (&rawtime);
#ifdef _MSC_VER
		localtime_s (&t_info, &rawtime);
	} else
		localtime_s (&t_info, &st.st_mtime);

  	strftime (buffer, 80, "Last-Modified:    , %d     %Y %H:%M:%S %Z\r\n", &t_info);
	strncpy_s(buffer+2+13, 80-2-13, wday_name[t_info.tm_wday], 3);
	strncpy_s(buffer+10+13, 80-10-13, mon_name[t_info.tm_mon], 3);
#else
  		t_info = localtime(&rawtime);
	} else
		t_info = localtime(&st.st_mtime);

	strftime (buffer, 80, "Last-Modified:    , %d     %Y %H:%M:%S %Z\r\n", t_info);
	strncpy_s(buffer+2+13, 80-2-13, wday_name[t_info->tm_wday], 3);
	strncpy_s(buffer+10+13, 80-10-13, mon_name[t_info->tm_mon], 3);
#endif
	connex->Send(buffer);
}

char *HTTP_Transform_Players_List()
{
	char *ret, *tmp = l_malloc(1);
	tmp[0] = 0;
	for (uint i=0; i<Sharun->Settings.Player_Max; i++) {
		if (Sharun->Players.Lists[i] && Sharun->Players.Lists[i]->loged > 0) {
			tmp = l_realloc(tmp, strlen(tmp)+4+(Sharun->Players.Lists[i]->Right >= 5 ? 5 : 0)+strlen(Sharun->Players.Lists[i]->name)+5+1);
			sprintf_s(tmp + strlen(tmp), 4+(Sharun->Players.Lists[i]->Right >= 5 ? 5 : 0)+strlen(Sharun->Players.Lists[i]->name)+5+1, "<li>%s%s</li>", Sharun->Players.Lists[i]->Right >= 5 ? "[GM] " : "", Sharun->Players.Lists[i]->name);
		}
	}
	ret = l_mem2mem(tmp);
	l_free(tmp);
	return ret;
}

char HTTP_Transform_Adjust(char **tmp, const char *src, char *dst, long dstLong)
{
	char *p = strstr(*tmp, src);
	if (!p) return 0;
	bool in_dst = false;
	if (!strcmp(src, "%PLAYERS_LIST%")) {
		dst = HTTP_Transform_Players_List();
		in_dst = true;
	}
	if (!dst) {
		dst = (char*)malloc(15);
		sprintf_s(dst, 15, "%ld", dstLong);
		in_dst = true;
	}
	char *tmpCPY = new char[strlen(p)-strlen(src)+1];
	strcpy_s(tmpCPY, strlen(p)-strlen(src)+1, p + strlen(src));
	long size = strlen(*tmp);
	size += strlen(dst);
	size -= strlen(src);
	*tmp = l_realloc(*tmp, size+1+100);
	p = strstr(*tmp, src);
	strncpy_s(p, strlen(dst) + 1, dst, strlen(dst));
	strncpy_s(p + strlen(dst), strlen(tmpCPY) + 1, tmpCPY, strlen(tmpCPY)+1);
	delete[] tmpCPY;
	if (in_dst) free(dst);
	return 1;
}

void HTTP_Transform_Change(char **tmp, bool html_file)
{
	char p;
	do {
		p = 0;
		if (!p) p = HTTP_Transform_Adjust(tmp, "%SERVER_NAME%", Sharun->Settings.Server_Name, 0);
		if (!p) p = HTTP_Transform_Adjust(tmp, "%SERVER_START_TIME%", Sharun->Settings.Start_Time, 0);
		if (!p) p = HTTP_Transform_Adjust(tmp, "%SERVER_START_COUNT%", NULL, Sharun->Settings.Start_Count);
		if (!p) p = HTTP_Transform_Adjust(tmp, "%SYSTEM_NAME%", (char*)SYSTEM_NAME, 0);
		if (!p) p = HTTP_Transform_Adjust(tmp, "%SYSTEM_VERSION%", (char*)SYSTEM_VERSION, 0);
		if (!p && html_file) p = HTTP_Transform_Adjust(tmp, "</body>", (char*)"\t%SERVER_SIGN%\n\t\t<sup>%SYSTEM_NAME% (%SYSTEM_VERSION%), a Tera server. Http server side.</sup>\n\t</BODY>", 0);
		if (!p && html_file) p = HTTP_Transform_Adjust(tmp, "<body>", (char*)"<BODY>", 0);
		if (!p && html_file) p = HTTP_Transform_Adjust(tmp, "</head>", (char*)"\t<!-- Created by Clofriwen, inspired from Tera Shock. http://forum.ragezone.com/f796/dev-sharun-dreams-1085405/ -->\n\t\t%SERVER_COPYRIGHT%\n\t</HEAD>", 0);
		if (!p && html_file) p = HTTP_Transform_Adjust(tmp, "<head>", (char*)"<HEAD>", 0);
		if (!p) p = HTTP_Transform_Adjust(tmp, "%SERVER_COPYRIGHT%", Sharun->Settings.SERVER_COPYRIGHT, 0);
		if (!p) p = HTTP_Transform_Adjust(tmp, "%SERVER_SIGN%", Sharun->Settings.SERVER_SIGN, 0);
		if (!p) p = HTTP_Transform_Adjust(tmp, "%PLAYERS_COUNT%", NULL, Sharun->Settings.PLAYER_COUNT);
		if (!p) p = HTTP_Transform_Adjust(tmp, "%PLAYERS_LIST%", NULL, 0);
	} while (p);
}

// Only on texts (html, js, css, ...) !!!
void HTTP_Transform(connexion_list *connex, bool noHead, FILE *fp, long size, bool http_head, const char *src)
{
	const char *ext = strrchr(src, '.');
	bool html_file = false;
	if (!strcmp(ext, ".html")) html_file = true;
	char *tmp = l_malloc(size+1);
	fread(tmp, 1, size, fp);
	tmp[size] = 0;
	HTTP_Transform_Change(&tmp, html_file);
	if (!noHead) {
		write_head_printf(connex, "Content-length: %ld\r\n", strlen(tmp));
		connex->Send("\r\n");
	}
	if (!http_head)
		connex->Send(tmp, strlen(tmp));
	l_free(tmp);
}

void HTTP_Direct(connexion_list *connex, bool noHead, FILE *fp, long start_pos, long size, bool http_head)
{
	fseek(fp, 0, SEEK_END);
	if (!noHead) {
		write_head_printf(connex, "Content-length: %ld\r\n", size);
		connex->Send("\r\n");
	}
	fseek(fp, start_pos, SEEK_SET);
	char tmp[1024];
	while (!http_head && !feof(fp)) {
		short r = fread(tmp, 1, 1024, fp);
		short s = connex->Send(tmp, r);
		if (s <= 0) return;
	}
}

void HTTP_MimeType(connexion_list *connex, char *src)
{
	char *ext = strrchr(src, '.');
	for (short i=0; mime_type[i][0]; i++) {
		if (ext && !strcmp(ext, mime_type[i][0])) {
			write_head_printf(connex, "Content-Type: %s\r\n", mime_type[i][1]);
			return;
		}
	}
	write_head_printf(connex, "Content-Type: %s\r\n", mime_type[0][1]);
}

bool HTTP_Can_Transform(char *src)
{
	char *ext = strrchr(src, '.');
	for (short i=0; Can_Transform[i]; i++) {
		if (ext && !strcmp(ext, Can_Transform[i]))
			return true;
	}
	return false;
}

bool getServerPVP(const char* Name)
{
	if (strstr(Name, "pvp"))
		return true;
	if (strstr(Name, "PvP"))
		return true;
	if (strstr(Name, "PVP"))
		return true;
	return false;
}

bool HTTP_test_IP_valide(char *IP)
{
	if (!IP || !strlen(IP))
		return false;
	char t_IP_t[41];
	strcpy_s(t_IP_t, 41, IP);
	char *p = strchr(t_IP_t, '.');
	p[0] = 0;
	if (atoi(t_IP_t))
		return true;
	return false;
}

void HTTP_Init()
{
	memset(NET_IP[0], 0, 16);
	memset(NET_IP[1], 0, 16);

	DEBUG("%s (%i) :: Get IP for Intranet...\n", __func__, __LINE__);
#ifdef WIN32
	char szHostName[255];
	gethostname(szHostName, 255);
	struct hostent *host_entry;
	host_entry = gethostbyname(szHostName);
	short i = 0;
	while (host_entry->h_addr_list[i])
		i++;
	i--;
	inet_ntop(AF_INET, (struct in_addr*) host_entry->h_addr_list[i], NET_IP[0], 16);
#else
	struct ifaddrs *addrs, *tmp;
	getifaddrs(&addrs);
	for (tmp = addrs; tmp; tmp = tmp->ifa_next) {
		if (tmp->ifa_addr && tmp->ifa_addr->sa_family == AF_INET) {
			if (!strcmp(tmp->ifa_name, "lo")) continue;
			struct sockaddr_in *pAddr = (struct sockaddr_in *)tmp->ifa_addr;
			strncpy_s(NET_IP[0], 16, inet_ntoa(pAddr->sin_addr), 15);
			break;
	      }
	}
	freeifaddrs(addrs);
#endif
	char t_IP_t[41];
	strcpy_s(t_IP_t, 41, NET_IP[0]);
	char *IP = t_IP_t;
	for (uchar i=0; i<2; i++) {
		char *p = strchr(IP, '.');
		if (p) {
			p[0] = 0;
			N_IP[i] = atoi(IP);
			IP = p + 1;
		}
	}
	DEBUG("\t%s\n", NET_IP[0]);

	DEBUG("%s (%i) :: Get IP for Internet", __func__, __LINE__);
	if (Sharun->Settings.Net.localhost) {
		strcpy_s(NET_IP[1], 16, "127.0.0.1");
		DEBUG(" (localhost)...\n");
	} else {
		if (HTTP_test_IP_valide(Sharun->Settings.Net.IP)) {
			DEBUG(" (from Config)...\n");
			memcpy(NET_IP[1], Sharun->Settings.Net.IP, 15);
		} else {
			DEBUG(" (from Internet)...\n");
			char *wget_r = NULL;
			wget_r = Network->WGet("http://checkip.dyndns.com/");
			if (wget_r) {
				IP = strstr(wget_r, ": ");
				IP = strstr(IP, "<");
				IP[0] = 0;
				IP = strstr(wget_r, ": ") + 2;
				strncpy_s(NET_IP[1], 16, IP, 15);
			}
		}

		if (!NET_IP[1][0]) {
			DEBUG("\tCan not resolve Internet IP. Will use from Intranet IP.\n");
			strncpy_s(NET_IP[1], 16, NET_IP[0], 15);
		}
	}
	DEBUG("\t%s\n", NET_IP[1]);
}

const char *getServerIP(const char* IP_src)
{
	if (!strcmp(IP_src, "127.0.0.1"))
		return "127.0.0.1";

	uchar t_IP[2];
	char t_IP_t[41];
	strcpy_s(t_IP_t, 41, IP_src);
	char *IP = t_IP_t;
	for (uchar i=0; i<2; i++) {
		char *p = strchr(IP, '.');
		p[0] = 0;
		t_IP[i] = atoi(IP);
		IP = p + 1;
	}

	if (N_IP[0] == 10
			&& t_IP[0] == 10)
		return NET_IP[0];
	if (N_IP[0] == 192 && N_IP[1] == 168
			&& t_IP[0] == 192 && t_IP[1] == 168)
		return NET_IP[0];
	if (N_IP[0] == 172 && N_IP[1] >= 16 && N_IP[1] <= 31
			&& t_IP[0] == 172 && t_IP[1] >= 16 && t_IP[1] <= 31)
		return NET_IP[0];

	return NET_IP[1];
}

void HTTP_Work(httpd_link_t *httpd_link)
{
	connexion_list *connex = httpd_link->connex;
	bool http_head = false;
	long f_size = 0;
	FILE *fp = NULL;
	char *WWW_PATH = l_realpath(Sharun->Settings.Dirs.WWW.c_str());
	WWW_PATH = (char*)realloc(WWW_PATH, strlen(WWW_PATH)+2);
	WWW_PATH[strlen(WWW_PATH)+1] = 0;
	WWW_PATH[strlen(WWW_PATH)] = '/';

	char HTML_Err_tmp[512];

	if (!memcmp(httpd_link->Head, "HEAD ", 5)) http_head = true;

	ushort e, b = 5;
	if (!memcmp(httpd_link->Head, "POST /", 6) || !memcmp(httpd_link->Head, "HEAD ", 5)) b = 6;
	if (!memcmp(httpd_link->Head, "TRACE /", 7)) b = 7;
	e = strstr(httpd_link->Head, " HTTP/") - httpd_link->Head;
	char *URL_PATH = (char*)malloc(e-b+1);
	memset(URL_PATH, 0, e-b+1);
	strncpy_s(URL_PATH, e-b+1, httpd_link->Head+b, e-b);

	if (!URL_PATH[0]) {
		URL_PATH = (char*)realloc(URL_PATH, 11);
		strcpy_s(URL_PATH, 11, "index.html");
	}

DEBUG("HTTP REQUESTED : \"%s\"\n", URL_PATH);
/*
HTTP REQUESTED : "servers/list.en"
HTTP REQUESTED : "servers/list.fr"
HTTP REQUESTED : "servers/list.uk"
HTTP REQUESTED : "servers/list.de"
*/

	char FILE_PATH_TMP[1024];
	sprintf_s(FILE_PATH_TMP, 1024, "%s%s", WWW_PATH, URL_PATH);
	char *FILE_PATH = l_realpath(FILE_PATH_TMP);

	if (!memcmp(httpd_link->Head, "POST ", 5) || !memcmp(httpd_link->Head, "TRACE ", 6))
		goto HTML_501;

	if (FILE_PATH) {
		if (strcmp(WWW_PATH, FILE_PATH) <= 0) {
			bool CanTrans = HTTP_Can_Transform(FILE_PATH_TMP);
			if (!httpd_link->noHead) {
				connex->Send("HTTP/1.0 200 OK\r\n");
				connex->Send("Connection: close\r\n");
				write_head_printf(connex, "Server: %s\r\n", DEFAULT_SERVER_NAME);
				HTTP_MimeType(connex, FILE_PATH_TMP);
				HTTP_DateTime_Char(connex, CanTrans, FILE_PATH_TMP);
			}
			f_size = file_size(FILE_PATH_TMP);
			fopen_s(&fp, FILE_PATH_TMP, "rb");
			if (fp) {
				if (CanTrans)
					HTTP_Transform(connex, httpd_link->noHead, fp, f_size, http_head, FILE_PATH_TMP);
				else
					HTTP_Direct(connex, httpd_link->noHead, fp, 0, f_size, http_head);
				fclose(fp);
				fp = NULL;
				goto HTML_DONE;
			} else goto HTML_404;
		} else goto HTML_403;
	} else goto HTML_404;

HTML_403:
	sprintf_s(HTML_Err_tmp, 512, "%s403.html", WWW_PATH);
	if (!httpd_link->noHead) {
		connex->Send("HTTP/1.0 403 OK\r\n");
		connex->Send("Connection: close\r\n");
		write_head_printf(connex, "Server: %s\r\n", DEFAULT_SERVER_NAME);
		HTTP_MimeType(connex, HTML_Err_tmp);
		HTTP_DateTime_Char(connex, true, HTML_Err_tmp);
	}
	f_size = file_size(HTML_Err_tmp);
	fopen_s(&fp, HTML_Err_tmp, "r");
	if (fp) {
		HTTP_Transform(connex, httpd_link->noHead, fp, f_size, http_head, HTML_Err_tmp);
		fclose(fp);
		fp = NULL;
		goto HTML_DONE;
	}

HTML_404:
	sprintf_s(HTML_Err_tmp, 512, "%s404.html", WWW_PATH);
	if (!httpd_link->noHead) {
		connex->Send("HTTP/1.0 404 OK\r\n");
		connex->Send("Connection: close\r\n");
		write_head_printf(connex, "Server: %s\r\n", DEFAULT_SERVER_NAME);
		HTTP_MimeType(connex, HTML_Err_tmp);
		HTTP_DateTime_Char(connex, true, HTML_Err_tmp);
	}
	f_size = file_size(HTML_Err_tmp);
	fopen_s(&fp, HTML_Err_tmp, "r");
	if (fp) {
		HTTP_Transform(connex, httpd_link->noHead, fp, f_size, http_head, HTML_Err_tmp);
		fclose(fp);
		fp = NULL;
		goto HTML_DONE;
	}

HTML_501:
	sprintf_s(HTML_Err_tmp, 512, "%s501.html", WWW_PATH);
	if (!httpd_link->noHead) {
		connex->Send("HTTP/1.0 501 OK\r\n");
		connex->Send("Connection: close\r\n");
		write_head_printf(connex, "Server: %s\r\n", DEFAULT_SERVER_NAME);
		HTTP_MimeType(connex, HTML_Err_tmp);
		HTTP_DateTime_Char(connex, true, HTML_Err_tmp);
	}
	f_size = file_size(HTML_Err_tmp);
	fopen_s(&fp, HTML_Err_tmp, "r");
	if (fp) {
		HTTP_Transform(connex, httpd_link->noHead, fp, f_size, http_head, HTML_Err_tmp);
		fclose(fp);
		fp = NULL;
		goto HTML_DONE;
	}

HTML_DONE:
	if (FILE_PATH) free(FILE_PATH);
	if (URL_PATH) free(URL_PATH);

	delete httpd_link;
	delete connex;
}
