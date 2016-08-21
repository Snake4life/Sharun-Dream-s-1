#include "Sharun.hpp"

void* C_EXIT_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_PREPARE_EXIT](args);

	return NULL;
}
