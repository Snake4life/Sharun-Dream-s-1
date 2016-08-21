#include <Dream/Dream.hpp>

#include "httpd_link.hpp"

#include <queue>

waiting_thd	HttpD_thd;
std::queue<httpd_link_t*> HttpD_queue;
Fixed_thread_W_t	HttpD_thread;

void HttpD_Add(httpd_link_t *httpd_link)
{
	pthread_mutex_lock(&HttpD_thread.mtx);
	HttpD_queue.push(httpd_link);
	HttpD_thd.resume();
	pthread_mutex_unlock(&HttpD_thread.mtx);
}

void HttpD_Cleanup()
{
	Fixed_thread_Cleanup(&HttpD_thread);
	while (!HttpD_queue.empty())
		HttpD_queue.pop();
}

void HttpD_Thread(thread_list *my_thread)
{
	httpd_link_t *httpd_link;
	Fixed_thread_t *http_thread_l;
	http_thread_l = Fixed_thread_Add(HttpD_Cleanup, &HttpD_thread, my_thread);
	while (my_thread->run) {
		pthread_mutex_lock(&HttpD_thread.mtx);
		if (HttpD_queue.empty()) {
			HttpD_thd.push(my_thread);
			pthread_mutex_unlock(&HttpD_thread.mtx);
			my_thread->wait();
		} else {
			httpd_link = HttpD_queue.front();
			HttpD_queue.pop();
			pthread_mutex_unlock(&HttpD_thread.mtx);
			HTTP_Work(httpd_link);
		}
	}
	Fixed_thread_Del(&HttpD_thread, http_thread_l);
	DEBUG("%s (%i) :: Httpd thread Stopped.\n", __FILE__, __LINE__);
	pthread_exit(NULL);
}
