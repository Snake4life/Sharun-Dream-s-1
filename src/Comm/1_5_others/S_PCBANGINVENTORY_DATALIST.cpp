#include "Sharun.hpp"

void* S_PCBANGINVENTORY_DATALIST_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_PCBANGINVENTORY_DATALIST, 8);

	packet_l->write_8(0);

	player_l->Send(packet_l);
	return NULL;
}
