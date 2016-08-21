#include "Sharun.hpp"

void* C_REQUEST_GAMESTAT_PING_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_RESPONSE_GAMESTAT_PONG](args);

	return NULL;
}
