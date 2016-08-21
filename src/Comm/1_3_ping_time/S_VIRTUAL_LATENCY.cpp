#include "Sharun.hpp"

void* S_VIRTUAL_LATENCY_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_VIRTUAL_LATENCY, 8);

	packet_l->write_4(0);
	packet_l->write_4(0);

	player_l->Send(packet_l);
	return NULL;
}
