#include <Sharun/Sharun.hpp>

#include <cstdarg>

SQL_QUEUE::SQL_QUEUE(const char *req, bool fast)
{
	stop = false;
	responce = true;
	Query = req;
	result = NULL;
	resume = NULL;
	if (fast) {
		resume = new pthread_pause_t;
		pthread_pause_init(resume, NULL);
	} else
		Query = strdump(req);
}

SQL_QUEUE::~SQL_QUEUE()
{
	if (resume) {
		pthread_pause_destroy(resume);
		delete resume;
	} else {
		if (Query)
			delete Query;
	}
}

bool SQL_QUEUE::is_Fast()
{
	if (resume)
		return true;
	return false;
}

void SQL_QUEUE::wait()
{
	pthread_pause_wait(resume);
}

void SQL_QUEUE::signal()
{
	pthread_pause_signal(resume);
}
