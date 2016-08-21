#include "Sharun.hpp"

void* C_RETURN_TO_LOBBY_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_PREPARE_RETURN_TO_LOBBY](args);

	return NULL;
}
