#include <Dream/Dream.hpp>

#include <cstdarg>

bool	is_MySQL_threaded();
bool	MySQL_Fast_Start();

void DB_Query_Add(SQL_QUEUE* query_l)
{
	if (is_MySQL_threaded())
		MySQL_Add(query_l);
}

uint DB_Max_Row(void* result)
{
	if (is_MySQL_threaded()) {
		MySQL_Conn *MySQL = (MySQL_Conn*) result;
		return mysql_num_rows(MySQL->res);
	}
	return 0;
}

void DB_Seek(void* result, ulong size)
{
	if (is_MySQL_threaded()) {
		MySQL_Conn *MySQL = (MySQL_Conn*) result;
		mysql_data_seek(MySQL->res, size);
	}
}

char** DB_Next_Row(void* result)
{
	if (is_MySQL_threaded()) {
		MySQL_Conn *MySQL = (MySQL_Conn*) result;
		return mysql_fetch_row(MySQL->res);
	}
	return NULL;
}

void DB_Result_Clear(void* result)
{
	if (is_MySQL_threaded()) {
		MySQL_Conn *MySQL = (MySQL_Conn*) result;
		MySQL->Clear();
	}
}

bool is_MySQL_threaded()
{
	if (Sharun->Settings.Thread.DataBase.Fast > 0)
		return true;
	return false;
}

void *DB_Query_Fast(uchar responce, const char *Query, ...)
{
	if (!Query)
		return NULL;
	void *ret = NULL;
	char req[1024];
	va_list __local_argv;
	va_start(__local_argv, Query );
	vsprintf_s(req, 1024, Query, __local_argv );
	va_end(__local_argv );
	if (is_MySQL_threaded()) {
		SQL_QUEUE *SQL_Comm = new SQL_QUEUE(req, true);
		switch (responce) {
			case 0:
				SQL_Comm->responce = false;
				break;
			case 2:
			default:
				SQL_Comm->responce = true;
		}
		DB_Query_Add(SQL_Comm);
		ret = SQL_Comm->result;
		delete SQL_Comm;
	}
	return ret;
}

void DB_Query_Slow(const char *Query, ...)
{
	if (!Query)
		return;
	char req[1024];
	va_list __local_argv;
	va_start(__local_argv, Query );
	vsprintf_s(req, 1024, Query, __local_argv );
	va_end(__local_argv );
	if (is_MySQL_threaded()) {
		SQL_QUEUE *SQL_Comm = new SQL_QUEUE(req, false);
		SQL_Comm->responce = false;
		DB_Query_Add(SQL_Comm);
	}
}

int DB_Query_int(int *ret, const char *Query, ...)
{
	if (!Query)
		return 0;
	int value;
	if (!ret)
		ret = &value;
	*ret = 0;
	char req[1024];
	va_list __local_argv;
	va_start(__local_argv, Query );
	vsprintf_s(req, 1024, Query, __local_argv );
	va_end(__local_argv );
	if (is_MySQL_threaded()) {
		SQL_QUEUE *SQL_Comm = new SQL_QUEUE(req, true);
		DB_Query_Add(SQL_Comm);
		char ** Row = DB_Next_Row(SQL_Comm->result);
		if (Row && Row[0])
			*ret = atoi(Row[0]);
		DB_Result_Clear(SQL_Comm->result);
		delete SQL_Comm;
	}
	return *ret;
}

long DB_Query_long(long *ret, const char *Query, ...)
{
	if (!Query)
		return 0;
	long value;
	if (!ret)
		ret = &value;
	*ret = 0;
	char req[1024];
	va_list __local_argv;
	va_start(__local_argv, Query );
	vsprintf_s(req, 1024, Query, __local_argv );
	va_end(__local_argv );
	if (is_MySQL_threaded()) {
		SQL_QUEUE *SQL_Comm = new SQL_QUEUE(req, true);
		DB_Query_Add(SQL_Comm);
		char ** Row = DB_Next_Row(SQL_Comm->result);
		if (Row && Row[0])
			*ret = atol(Row[0]);
		DB_Result_Clear(SQL_Comm->result);
		delete SQL_Comm;
	}
	return *ret;
}

float DB_Query_float(float *ret, const char *Query, ...)
{
	if (!Query)
		return 0;
	float value;
	if (!ret)
		ret = &value;
	*ret = 0.0;
	char req[1024];
	va_list __local_argv;
	va_start(__local_argv, Query );
	vsprintf_s(req, 1024, Query, __local_argv );
	va_end(__local_argv );
	if (is_MySQL_threaded()) {
		SQL_QUEUE *SQL_Comm = new SQL_QUEUE(req, true);
		DB_Query_Add(SQL_Comm);
		char ** Row = DB_Next_Row(SQL_Comm->result);
		if (Row && Row[0])
			*ret = atof2(Row[0]);
		DB_Result_Clear(SQL_Comm->result);
		delete SQL_Comm;
	}
	return *ret;
}

char16_t* DB_Query_S(char16_t *ret, const char *Query, ...)
{
	if (!Query)
		return 0;
	char req[1024];
	va_list __local_argv;
	va_start(__local_argv, Query );
	vsprintf_s(req, 1024, Query, __local_argv );
	va_end(__local_argv );
	if (is_MySQL_threaded()) {
		SQL_QUEUE *SQL_Comm = new SQL_QUEUE(req, true);
		DB_Query_Add(SQL_Comm);
		char ** Row = DB_Next_Row(SQL_Comm->result);
		if (Row && Row[0]) {
			if (ret)
				strcpy8_16(ret, Row[0]);
			else
				ret = str_str8_16(Row[0]);
		}
		DB_Result_Clear(SQL_Comm->result);
		delete SQL_Comm;
	}
	return ret;
}

char* DB_Query_char(char *ret, const char *Query, ...)
{
	if (!Query)
		return 0;
	char req[1024];
	va_list __local_argv;
	va_start(__local_argv, Query );
	vsprintf_s(req, 1024, Query, __local_argv );
	va_end(__local_argv );
	if (is_MySQL_threaded()) {
		SQL_QUEUE *SQL_Comm = new SQL_QUEUE(req, true);
		DB_Query_Add(SQL_Comm);
		char ** Row = DB_Next_Row(SQL_Comm->result);
		if (Row && Row[0]) {
			if (ret)
				strcpy_s(ret, 1024, Row[0]);
			else
				ret = strdump(Row[0]);
		}
		DB_Result_Clear(SQL_Comm->result);
		delete SQL_Comm;
	}
	return ret;
}

void database::start()
{
	thread_list *thread = NULL;
	if (is_MySQL_threaded()) {
		for (int i=0; DB_Set.Login && i < Sharun->Settings.Thread.DataBase.Fast; i++) {
			if (!MySQL_Fast_Start())
				DEBUG("%s (%i) :: Could not start MySQL thread %i !\n", __FILE__, __LINE__, i);
			else
				DEBUG("%s (%i) :: MySQL fast thread %i started.\n", __FILE__, __LINE__, i);
		}
		for (int i=0; DB_Set.Login && i < Sharun->Settings.Thread.DataBase.Slow; i++) {
			thread = new thread_list();
			if (!thread->start((void*)MySQL_Thread, thread))
				DEBUG("%s (%i) :: Could not start MySQL thread %i !\n", __FILE__, __LINE__, i);
			else
				DEBUG("%s (%i) :: MySQL slow thread %i started.\n", __FILE__, __LINE__, i);
		}
	}

	init_Items();
	init_Equipments();
	init_Zone();
	init_Friendly();
	init_Monster();
	init_Mounts();
}

database::~database()
{
	close_Equipments();
	close_Items();
	close_Friendly();
	close_Monster();
	close_Zone();
	close_Mounts();
}
