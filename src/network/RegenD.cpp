#include "Game_Regen.hpp"

//				NPC		PLAYER
//uchar waiting_annim[2][4] = { {1, 2, 3, 24}, {31, 32, 33} };

void RegenD_ReWait(player* player_l)
{
	player_l->Last_Move = time(NULL) + 3 + 15;
	player_l->Last_Move += rand() % 10;
}

void RegenD_DontWait(player* player_l)
{
	player_l->Last_Move = 0xFFFFFFFFFFFFFFFF;
}

void RegenD_Thread(game_regen_t* Game_Regen)
{
	while (Game_Regen->my_thread->run && Game_Regen->st_thread->run) {
			Game_Regen->my_thread->wait();
		if (Game_Regen->player_l)
			Game_Regen->player_l->regen(Game_Regen->my_thread);
	}
	DEBUG("%s (%i) :: RegenD thread Stopped.\n", __FILE__, __LINE__);
	pthread_exit(NULL);
}
