#include "Sharun.hpp"

void* C_REQUEST_VIP_SYSTEM_INFO_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_SEND_VIP_SYSTEM_INFO](args);

	return NULL;
}
