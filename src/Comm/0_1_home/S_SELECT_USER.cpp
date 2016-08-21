#include "Sharun.hpp"

void* S_SELECT_USER_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_SELECT_USER, 9);

	packet_l->write_1(1);
	packet_l->write_8(0);

	player_l->Send(packet_l);
	return NULL;
}
