#ifndef _DB_HPP_
#define _DB_HPP_

#include "pthread_sub.hpp"

#include "DB/DB_character_appearances.hpp"
#include "DB/DB_character_detail_2.hpp"
#include "DB/DB_character_items.hpp"
#include "DB/DB_character_skill.hpp"
#include "DB/DB_character_skill2.hpp"
#include "DB/DB_characters.hpp"
#include "DB/DB_template.hpp"
#include "DB/DB_Friends_List.hpp"

class SQL_QUEUE {
	protected:
		pthread_pause_t *resume;

	public:
		SQL_QUEUE(const char *req, bool fast);
		virtual ~SQL_QUEUE();
		bool	is_Fast();
		void	wait();
		void	signal();
		bool	responce;
		bool	stop;
		const char*	Query;
		void*	result;
};

#ifdef _WINDLL
extern void	(*DB_Query_Add)(SQL_QUEUE*);
extern uint	(*DB_Max_Row)(void *Result);
extern void	(*DB_Seek)(void *Result, ulong pos);
extern char**	(*DB_Next_Row)(void *Result);
extern void	(*DB_Result_Clear)(void *Result);
extern void*	(*DB_Query_Fast)(uchar responce, const char *Query, ...);
extern void	(*DB_Query_Slow)(const char *Query, ...);
extern int	(*DB_Query_int)(int *ret, const char *Query, ...);
extern long	(*DB_Query_long)(long *ret, const char *Query, ...);
extern float	(*DB_Query_float)(float *ret, const char *Query, ...);
extern char16_t*	(*DB_Query_S)(char16_t *ret, const char *Query, ...);
extern char*	(*DB_Query_char)(char *ret, const char *Query, ...);
#else
extern "C" {
void	DB_Query_Add(SQL_QUEUE*);
uint	DB_Max_Row(void *Result);
void	DB_Seek(void *Result, ulong pos);
char**	DB_Next_Row(void *Result);
void	DB_Result_Clear(void *Result);
void*	DB_Query_Fast(uchar responce, const char *Query, ...);
void	DB_Query_Slow(const char *Query, ...);
int	DB_Query_int(int *ret, const char *Query, ...);
long	DB_Query_long(long *ret, const char *Query, ...);
float	DB_Query_float(float *ret, const char *Query, ...);
char16_t*	DB_Query_S(char16_t *ret, const char *Query, ...);
char*	DB_Query_char(char *ret, const char *Query, ...);
}
#endif // _WINDLL

#endif // _DB_HPP_
