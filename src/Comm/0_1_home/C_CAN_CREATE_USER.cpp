#include "Sharun.hpp"

void* C_CAN_CREATE_USER_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_CAN_CREATE_USER](args);

	return NULL;
}
