#include "Sharun.hpp"

void* C_UPDATE_FRIEND_INFO_f(player* player_l, packet* packet_l)
{
	const void *args[] = {player_l, NULL};

	Sharun->OpCodes.Send[S_USER_BLOCK_LIST](args);
	Sharun->OpCodes.Send[S_FRIEND_GROUP_LIST](args);
	Sharun->OpCodes.Send[S_FRIEND_LIST](args);
	Sharun->OpCodes.Send[S_UPDATE_FRIEND_INFO](args);

	return NULL;
}
