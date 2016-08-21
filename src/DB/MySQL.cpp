#include <Dream/Dream.hpp>

#include <tbb/tbb.h>

tbb::concurrent_queue<MySQL_Conn*> MySQL_Fast_queue;
tbb::concurrent_queue<SQL_QUEUE*> SQL_Conn_Fast_queue;

waiting_thd MySQL_Slow_thd;
tbb::concurrent_queue<SQL_QUEUE*> MySQL_Slow_queue;
Fixed_thread_W_t	MySQL_Slow_thread;

bool MySQL_queue_enabled = true;


MySQL_Conn::MySQL_Conn(bool fast)
{
	_fast = fast;
	res = NULL;
	_conn = mysql_init(NULL);
	if (!_conn || !mysql_real_connect(_conn, DB->DB_Set.IP, DB->DB_Set.Login, DB->DB_Set.Pass,
			DB->DB_Set.Name, DB->DB_Set.Port, NULL, CLIENT_SSL)) {
		DEBUG("%s (%i) :: %s\n", __func__, __LINE__, mysql_error(_conn));
		mysql_close(_conn);
		_conn = NULL;
	} else {
		bool reconnect = true;
		mysql_options((_conn), MYSQL_OPT_RECONNECT, &reconnect);
//#ifdef mysql_set_character_set
		if (mysql_set_character_set((_conn), "utf8"))
			DEBUG("%s (%i) :: %s\n", __func__, __LINE__, mysql_error(_conn));
//#endif
	}
}

MySQL_Conn::~MySQL_Conn()
{
	mysql_close(_conn);
	_conn = NULL;
}

void MySQL_Conn::Clear()
{
	if (res)
		mysql_free_result(res);
	res = NULL;
	if (_fast) {
		MySQL_Fast_queue.push(this);
		SQL_QUEUE *SQL_Comm = NULL;
		if (SQL_Conn_Fast_queue.try_pop(SQL_Comm))
			SQL_Comm->signal();
	}
}

bool MySQL_Conn::is_conn()
{
	if (_conn)
		return true;
	return false;
}

void MySQL_Conn::Work(SQL_QUEUE* SQL_Comm)
{
	if (res)
		mysql_free_result(res);
	res = NULL;
	mysql_query(_conn, SQL_Comm->Query);
	if (mysql_error(_conn)[0])
		DEBUG("%s (%i) :: %s : \"%s\"\n", __func__, __LINE__, mysql_error(_conn), SQL_Comm->Query);
		res = mysql_use_result(_conn);
	if (!_fast) {
		if (SQL_Comm->Query)
			delete[] SQL_Comm->Query;
		if (res)
			mysql_free_result(res);
		res = NULL;
	} else {
		if (!SQL_Comm->responce) {
			Clear();
		} else {
			SQL_Comm->result = this;
		}
	}
}

bool MySQL_Fast_Start()
{
	MySQL_Conn *MySQL = new MySQL_Conn(true);
	if (!MySQL || !MySQL->is_conn()) {
		delete MySQL;
		return false;
	}
	MySQL_Fast_queue.push(MySQL);
	return true;
}

void MySQL_Fast_Stop()
{
	MySQL_Conn *MySQL = NULL;
	short i = 0;
	SQL_QUEUE *_queue = new SQL_QUEUE("", true);
	while (i < Sharun->Settings.Thread.DataBase.Fast) {
		if (MySQL_Fast_queue.try_pop(MySQL)) {
			delete MySQL;
			i++;
			DEBUG("%s (%i) :: MySQL Faster Stopped.\n", __FILE__, __LINE__);
		} else {
			SQL_Conn_Fast_queue.push(_queue);
			_queue->wait();
		}
	}
	delete _queue;
}

void MySQL_Add(SQL_QUEUE *SQL_Comm)
{
	if (!MySQL_queue_enabled)
		return;
	if (SQL_Comm->is_Fast()) {
		MySQL_Conn* MySQL = NULL;
		while (!MySQL_Fast_queue.try_pop(MySQL) && !SQL_Comm->stop) {
			SQL_Conn_Fast_queue.push(SQL_Comm);
			SQL_Comm->wait();
		}
		if (!SQL_Comm->stop)
			MySQL->Work(SQL_Comm);
	} else  {
		MySQL_Slow_queue.push(SQL_Comm);
		MySQL_Slow_thd.resume();
	}
}

void MySQL_Cleanup()
{
	MySQL_queue_enabled = false;
	Fixed_thread_Cleanup(&MySQL_Slow_thread);
	SQL_QUEUE* SQL_Comm = NULL;
	while (!MySQL_Slow_queue.empty()) {
		if (MySQL_Slow_queue.try_pop(SQL_Comm))
			delete SQL_Comm;
	}
	while (!SQL_Conn_Fast_queue.empty()) {
		if (SQL_Conn_Fast_queue.try_pop(SQL_Comm)) {
			SQL_Comm->stop = true;
			SQL_Comm->signal();
		}
	}
	MySQL_Fast_Stop();
}

void MySQL_Thread(thread_list *my_thread)
{
	MySQL_Conn *MySQL = new MySQL_Conn(false);

	if (!MySQL->is_conn()) {
		DEBUG("%s (%i) :: MySQL Slower not started !\n", __FILE__, __LINE__);
		delete MySQL;
		delete my_thread;
	} else {
		DEBUG("%s (%i) :: MySQL Slower Started.\n", __FILE__, __LINE__);

		SQL_QUEUE* SQL_Comm = NULL;
		Fixed_thread_t *MySQL_thread_l = NULL;

		MySQL_thread_l = Fixed_thread_Add(MySQL_Cleanup, &MySQL_Slow_thread, my_thread);

		while (my_thread->run) {
			SQL_Comm = NULL;
			if (!MySQL_Slow_queue.try_pop(SQL_Comm)) {
				MySQL_Slow_thd.push(my_thread);
				my_thread->wait();
			} else {
				if (SQL_Comm) {
					MySQL->Work(SQL_Comm);
					delete SQL_Comm;
				}
			}
		}

		delete MySQL;
		Fixed_thread_Del(&MySQL_Slow_thread, MySQL_thread_l);
		DEBUG("%s (%i) :: MySQL Slower Stopped.\n", __FILE__, __LINE__);
	}
	pthread_exit(NULL);
}
