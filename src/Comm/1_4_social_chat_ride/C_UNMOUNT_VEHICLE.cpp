#include "Sharun.hpp"

void* C_UNMOUNT_VEHICLE_f(player* player_l, packet* packet_l)
{
	World_PlayerMount(player_l, false, 0);
	return NULL;
}
