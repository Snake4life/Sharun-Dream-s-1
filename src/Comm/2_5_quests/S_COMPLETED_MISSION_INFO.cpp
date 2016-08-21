#include "Sharun.hpp"

void* S_COMPLETED_MISSION_INFO_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_COMPLETED_MISSION_INFO, 4);

	packet_l->write_4(0);

	player_l->Send(packet_l);
	return NULL;
}
