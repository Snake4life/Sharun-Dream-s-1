#include <Sharun/Sharun.hpp>

#include <cstdarg>
#include <ctype.h>

#include <sys/stat.h>
#include <sys/types.h>

#ifndef _MSC_VER
#include <sys/time.h>
#include <unistd.h>
#endif

uint l_sizeof(char *src)
{
	if (!src) return 0;
	uint i;
	memcpy(&i, src - sizeof(uint), sizeof(uint)); 
	return i;
}

char *l_malloc(uint size)
{
	char *out = (char*)malloc(size + sizeof(uint));
	memcpy(out, &size, sizeof(uint)); 
	return out + sizeof(uint);
}

void l_free(char *src)
{
	free(src - sizeof(uint));
}

char *l_realloc(char *src, uint size)
{
	char *out = (char*)realloc(src ? src - sizeof(uint) : NULL, size + sizeof(uint));
	if (!out) {
		out = l_malloc(size);
		memcpy(out, src, l_sizeof(src));
		l_free(src);
	} else out += sizeof(uint);
	memcpy(out - sizeof(uint), &size, sizeof(uint));
	return out;
}

char *l_mem2mem(char *src)
{
	if (!src) return NULL;
	char *out = (char*)malloc(l_sizeof(src));
	if (out)
		memcpy(out, src, l_sizeof(src));
	return out;
}

char *bytedump(const char *value)
{
	size_t size = sizeof(value)/sizeof(*value);
	char *dst = (char*)malloc(size);
	memcpy(dst, value, size);
	return dst;
}

char *strdump(const char *value)
{
	char *dst = new char[strlen(value)+1];
	strcpy_s(dst, strlen(value) + 1, value);
	return dst;
}

char *strndump(const char *value, int len)
{
	char *dst = new char[len+1];
	memset(dst, 0, len+1);
	strncpy_s(dst, len + 1, value, len);
	return dst;
}

void strupdate(char **src, const char *value)
{
	if (*src) delete (*src);
	*src = strdump(value);
}

char dir_exist(const char *dirname)
{
  struct stat   buffer;   
  if( stat( dirname, &buffer ) != 0 )
    return 0;
#ifdef WIN32
  else if( buffer.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows 
#else
  else if( S_ISDIR(buffer.st_mode) )
#endif
    return 1;
  return 0;
}

char file_exist(const char *filename)
{
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}

size_t file_size(const char *filename)
{
  struct stat   buffer;   
  stat (filename, &buffer);
  return buffer.st_size;
}

void l_mkdir(const char* dirname)
{
#ifdef WIN32
#ifndef _MSC_VER
	mkdir(dirname);
#else
	CreateDirectory((LPCTSTR) dirname, NULL);
#endif // _MSC_VER
#else
  mkdir(dirname, 0777);
#endif

}

float atof2(char* val)
{
	char *tmp = strchr(val, ',');
	if (tmp)
		tmp[0] = '.';
	return atof(val);
}

bool atob(char* val)
{
	if (strlen(val) > 0) {
		if (tolower(val[0]) == 't')
			return true;
		if (tolower(val[0]) == 'y')
			return true;
		if (val[0] == '1')
			return true;
	}
	return false;
}

short is_atoi(char* val)
{
  while (val[0]) {
    if ( val[0] != '-'
      && val[0] != '0'
      && val[0] != '1'
      && val[0] != '2'
      && val[0] != '3'
      && val[0] != '4'
      && val[0] != '5'
      && val[0] != '6'
      && val[0] != '7'
      && val[0] != '8'
      && val[0] != '9'
    ) return 0;
    val++;
  }
  return 1;
}

bool between(uint value, bool included, uint start, uint end)
{
	if (included && value >= start && value <= end)
		return true;
	if (!included && value > start && value < end)
		return true;
	return false;
}

#ifdef _MSC_VER
#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif
#endif // _MSC_VER
ulong millisec()
{
#ifndef _MSC_VER
	struct timeval time;
	gettimeofday(&time, NULL);
	ulong microsec = time.tv_sec;
	microsec *= 1000000;
	microsec += time.tv_usec;
	return microsec / 1000;
#else
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	GetSystemTimeAsFileTime(&ft);
	tmpres |= ft.dwHighDateTime;
	tmpres <<= 32;
	tmpres |= ft.dwLowDateTime;
	tmpres -= DELTA_EPOCH_IN_MICROSECS; 
	tmpres /= 10;  /*convert into microseconds*/
	return (long)(tmpres / 1000UL);
#endif
}

char* l_realpath(const char * src)
{
	char * buffer;
#ifdef WIN32
	buffer = (char*)malloc(4092);
	GetFullPathNameA(src, 4092, buffer, NULL);
	buffer = (char*)realloc(buffer, strlen(buffer)+1);
#else
	buffer = realpath(src, NULL);
#endif
	return buffer;
}

void hexdump(const char* function, const char* title, const void *Vbuffer, unsigned long index)
{
	const unsigned char *buffer = (const unsigned char*)Vbuffer;
	DEBUG("%s (%i) :: %s :: %s (%ld)\n", __func__, __LINE__, function, title, index);
	for (unsigned long i=0; i<index; i+=16) {
		DEBUG2("[%10ld]\t", i);
		for (int spacer=0; spacer<16; spacer++) {
			if (i+spacer >= index)
				DEBUG2("   ");
			else
				DEBUG2("%02X ", buffer[i+spacer]);
			if ((spacer+1)/4 == (float)(spacer+1)/4)
				DEBUG2(" ");
		}
		DEBUG2("\t: ");
		for (int spacer=0; spacer<16; spacer++) {
			if (i+spacer >= index)
				DEBUG2("   ");
			else {
				if (buffer[i+spacer] < 32) DEBUG2(".");
				else DEBUG2("%c",buffer[i+spacer]);
			}
		}
		DEBUG2("\n");
	}
	DEBUG2("\n");
}


int SQL_Check_Char(char *data)
{
	int i=0;
	char* F = data-1;
	do {
		F++;
		F = strchr(F, '\'');
		if (F)
			i++;
	} while (F);
	return i;
}

void SQL_Format_Char(char *data)
{
	char* F = data-1;
	do {
		F++;
		F = strchr(F, '\'');
		if (F) {
			char tmp[512];
			strcpy_s(tmp, 512, F);
			strcpy_s(&F[1], strlen(&F[1]) + 2, tmp);
			F++;
		}
	} while (F);
}

void SQL_toFloat(char *val)
{
	char *tmp = strchr(val, '.');
	if (tmp)
		tmp[0] = ',';
}
