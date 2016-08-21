#ifndef _DB_SETTING_HPP_
#define _DB_SETTING_HPP_

#include <mysql.h>

typedef struct database_setting {
	char	IP[8*4+7+1];
	ushort	Port;
	char*	Login;
	char*	Pass;
	char*	Name;
	std::string SQLite;
	std::string RAW_Files;
} database_setting;

class MySQL_Conn {
	public:
		MySQL_Conn(bool fast);
		~MySQL_Conn();
		bool	is_conn();
		void	Work(SQL_QUEUE*);
		void	Clear();
		MYSQL_RES*	res;

	protected:
		MYSQL*	_conn;
		bool	_fast;
};

class database {
	public:
		database_setting DB_Set;
		void start();
		~database();
};

extern database* DB;

void	MySQL_Add(SQL_QUEUE*);
void	MySQL_Cleanup();
void	MySQL_Thread(thread_list *my_thread);


void	init_Items();
item*	get_Item(uint);
void	close_Items();

void	init_Equipments();
item*	get_Equipment(uint);
void	close_Equipments();


void	init_Zone();
void	get_Zone(player*, uint);
void	get_ZoneDJ(player*, uint);
void	close_Zone();


void	init_Friendly();
void	close_Friendly();


void	init_Monster();
void	close_Monster();


void	init_Mounts();
mount*	get_Mount(uint);
void	close_Mounts();

#endif // _DB_SETTING_HPP_
