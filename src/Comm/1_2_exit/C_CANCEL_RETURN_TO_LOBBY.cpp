#include "Sharun.hpp"

void* C_CANCEL_RETURN_TO_LOBBY_f(player* player_l, packet* packet_l)
{
	player_l->exit_type = 0;
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_CANCEL_RETURN_TO_LOBBY](args);

	return NULL;
}
