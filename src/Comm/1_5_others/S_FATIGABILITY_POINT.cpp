#include "Sharun.hpp"

void* S_FATIGABILITY_POINT_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_FATIGABILITY_POINT, 8);

	packet_l->write_4(1);
	packet_l->write_4(4000);

	player_l->Send(packet_l);
	return NULL;
}
