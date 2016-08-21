#include "Sharun.hpp"

void* S_MY_DESCRIPTION_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_MY_DESCRIPTION, 4);

	packet_l->write_4(6);

	player_l->Send(packet_l);
	return NULL;
}
