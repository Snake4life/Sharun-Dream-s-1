#include "Sharun.hpp"

void* S_RESPONSE_GAMESTAT_PONG_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_RESPONSE_GAMESTAT_PONG, 0);
	player_l->Send(packet_l);
	return NULL;
}
