#include <Dream/Dream.hpp>

typedef struct game_regen_t {
	thread_list*	st_thread;
	thread_list*	my_thread;
	player*	player_l;
} game_regen_t;

void RegenD_Thread(game_regen_t*);
