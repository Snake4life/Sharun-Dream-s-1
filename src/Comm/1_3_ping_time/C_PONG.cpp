#include "Sharun.hpp"

void* C_PONG_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_PING](args);

	return NULL;
}
