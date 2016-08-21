#include "Sharun.hpp"

void* S_PING_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_PING, 0);
	player_l->Send(packet_l);
	return NULL;
}
