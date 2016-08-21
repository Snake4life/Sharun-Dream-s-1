#include "Sharun.hpp"

void* C_SKILL_LEARN_LIST_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_SKILL_LEARN_LIST](args);

	return NULL;
}
