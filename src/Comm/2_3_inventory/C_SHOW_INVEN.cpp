#include "Sharun.hpp"

void* C_SHOW_INVEN_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, player_l};

	Sharun->OpCodes.Send[S_INVEN](args);

	return NULL;
}
