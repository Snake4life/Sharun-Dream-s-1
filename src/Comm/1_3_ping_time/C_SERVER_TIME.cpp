#include "Sharun.hpp"

void* C_SERVER_TIME_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_SERVER_TIME](args);

	return NULL;
}
