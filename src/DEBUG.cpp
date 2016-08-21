#include <Dream/Dream.hpp>
#include <cstdarg>

#include <ctype.h>

#ifndef _MSC_VER
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#ifndef NO_ERROR_FILE
FILE * FError = NULL;
#else
#define FError stderr
#endif

void DEBUG(const char *__msg, ...)
{
	if (!FError) return;
	if (!__msg) {
		fprintf(FError, "\n");
		return;
	}
	if (FError != stderr) {
		time_t rawtime;
		time ( &rawtime );
#ifdef _MSC_VER
		struct tm t_info;
		localtime_s(&t_info,  &rawtime);
		fprintf(FError, "[%04i-%02i-%02i %02i:%02i:%02i] ", t_info.tm_year+1900, t_info.tm_mon+1, t_info.tm_mday, t_info.tm_hour, t_info.tm_min, t_info.tm_sec);
#else
		struct tm* t_info;
		t_info = localtime(&rawtime);
		fprintf(FError, "[%04i-%02i-%02i %02i:%02i:%02i] ", t_info->tm_year+1900, t_info->tm_mon+1, t_info->tm_mday, t_info->tm_hour, t_info->tm_min, t_info->tm_sec);
#endif
	}
	va_list __local_argv;
	va_start(__local_argv, __msg );
	vfprintf(FError, __msg, __local_argv );
	va_end(__local_argv );
	fflush(FError);
}

void DEBUG2(const char *__msg, ...)
{
	if (!FError) return;
	va_list __local_argv;
	va_start(__local_argv, __msg );
	vfprintf(FError, __msg, __local_argv );
	va_end(__local_argv );
	fflush(FError);
}
