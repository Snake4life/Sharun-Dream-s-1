#ifndef _FIXED_THREAD_HPP_
#define _FIXED_THREAD_HPP_

typedef struct Fixed_thread_t {
	thread_list*	thread;
	Fixed_thread_t*	next;
	Fixed_thread_t*	prev;
} Fixed_thread_t;

class Fixed_thread_W_t {
	public:
		Fixed_thread_W_t();
		bool init;
		pthread_mutex_t	mtx;
		Fixed_thread_t*	threads[2];
};

void Fixed_thread_Close();
void Fixed_thread_Close_Add(void (*)());

void Fixed_thread_Cleanup(Fixed_thread_W_t*);
Fixed_thread_t *Fixed_thread_Add(void (*)(), Fixed_thread_W_t*, thread_list*);
void Fixed_thread_Del(Fixed_thread_W_t*, Fixed_thread_t*);

class waiting_thd {
	protected:
		Fixed_thread_t* Lists[2];

	public:
		waiting_thd();
		~waiting_thd();
		void	push(thread_list*);
		void	resume();
		bool	empty();
};

#endif // _FIXED_THREAD_HPP_
