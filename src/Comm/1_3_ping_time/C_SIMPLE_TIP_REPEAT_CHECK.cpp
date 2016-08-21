#include "Sharun.hpp"

void* C_SIMPLE_TIP_REPEAT_CHECK_f(player* player_l, packet* packet_l)
{
	uint va = packet_l->read_4();
	const void *args[] = {player_l, &va, NULL};

	Sharun->OpCodes.Send[S_SIMPLE_TIP_REPEAT_CHECK](args);

	return NULL;
}
