#include "Sharun.hpp"

void* C_SOCIAL_f(player* player_l, packet* packet_l)
{
	uint id = packet_l->read_4();
	World_PlayerSocial(player_l, true, id);
	return NULL;
}
