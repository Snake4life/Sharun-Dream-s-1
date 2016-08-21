#include "Sharun.hpp"

void* S_MOVE_DISTANCE_DELTA_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_MOVE_DISTANCE_DELTA, 4);

	packet_l->write_F(200);

	player_l->Send(packet_l);
	return NULL;
}
