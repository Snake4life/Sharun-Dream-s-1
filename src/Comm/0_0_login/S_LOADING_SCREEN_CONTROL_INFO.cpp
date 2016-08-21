#include "Sharun.hpp"

void* S_LOADING_SCREEN_CONTROL_INFO_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_LOADING_SCREEN_CONTROL_INFO, 1);

	packet_l->write_1(0);

	player_l->Send(packet_l);
	return NULL;
}
