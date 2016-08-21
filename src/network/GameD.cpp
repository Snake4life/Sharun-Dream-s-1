#include "Game_Regen.hpp"

#include <queue>


waiting_thd	GameD_thd;
std::queue<player*> GameD_queue;
Fixed_thread_W_t	GameD_thread;

void GameD_Add(player* player_l)
{
	pthread_mutex_lock(&GameD_thread.mtx);
	GameD_queue.push(player_l);
	/* Send Queue Pos
	const void *args[] = {player_l, NULL, NULL};
	Sharun->OpCodes.Send[S_WAITING_LIST](args);*/
	GameD_thd.resume();
	pthread_mutex_unlock(&GameD_thread.mtx);
}

void GameD_Cleanup()
{
	Fixed_thread_Cleanup(&GameD_thread);
	while (!GameD_queue.empty())
		GameD_queue.pop();
}

void GameD_Thread(thread_list* my_thread)
{
	Fixed_thread_t*	GameD_thread_l;
	GameD_thread_l = Fixed_thread_Add(GameD_Cleanup, &GameD_thread, my_thread);
	thread_list*	RegenD_thread = new thread_list();
	game_regen_t	Game_Regen = { my_thread, RegenD_thread, NULL };
	if (!RegenD_thread->start((void*)RegenD_Thread, &Game_Regen)) {
		DEBUG("%s (%i) :: Could not start RegenD thread !\n", __FILE__, __LINE__);
		Fixed_thread_Del(&GameD_thread, GameD_thread_l);
		DEBUG("%s (%i) :: GameD thread Stopped.\n", __FILE__, __LINE__);
		pthread_exit(NULL);
	} else
		DEBUG("%s (%i) :: RegenD thread started.\n", __FILE__, __LINE__);
	while (my_thread->run) {
		pthread_mutex_lock(&GameD_thread.mtx);
		Game_Regen.player_l = NULL;
		if (GameD_queue.empty()) {
			GameD_thd.push(my_thread);
			pthread_mutex_unlock(&GameD_thread.mtx);
			my_thread->wait();
		} else {
			player *player_l = GameD_queue.front();
			GameD_queue.pop();
			/* Update Queue Pos of other
			const void *args[] = {player_l, &S_LOGIN_ARBITER_var, NULL};
			Sharun->OpCodes.Send[???](args);*/
			pthread_mutex_unlock(&GameD_thread.mtx);
			pthread_mutex_lock(&Sharun->Players.mtx);
			ushort Players_ID = 0;
			while (Sharun->Players.Lists[Players_ID]) {
				if (Players_ID >= Sharun->Settings.Player_Max){
					Players_ID = 0;
					pthread_mutex_unlock(&Sharun->Players.mtx);
					Sleep(1);
					pthread_mutex_lock(&Sharun->Players.mtx);
				} else
					Players_ID++;
			}
			Sharun->Players.Lists[Players_ID] = player_l;
			player_l->Players_ID = Players_ID;
			pthread_mutex_unlock(&Sharun->Players.mtx);
			// Ok, Let's Play
			Game_Regen.player_l = player_l;
			RegenD_thread->signal();
			player_l->start(my_thread);
			Game_Regen.player_l = NULL;
			if (player_l->connex) {
				player_l->connex->Player = NULL;
				delete player_l->connex;
				player_l->connex = NULL;
			}
			pthread_mutex_lock(&Sharun->Players.mtx);
			Sharun->Players.Lists[Players_ID] = NULL;
			pthread_mutex_unlock(&Sharun->Players.mtx);
			if (player_l->loged)
				World_Exit(player_l);
			DEBUG("%s (%i) :: GameD thread cleanning player.\n", __FILE__, __LINE__);
			delete player_l;
			player_l = NULL;
		}
	}
	RegenD_thread->join();
	Fixed_thread_Del(&GameD_thread, GameD_thread_l);
	DEBUG("%s (%i) :: GameD thread Stopped.\n", __FILE__, __LINE__);
	pthread_exit(NULL);
}
