#include "Sharun.hpp"

void* S_ONGOING_HUNTING_EVENT_LIST_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_ONGOING_HUNTING_EVENT_LIST, 4);

	packet_l->write_4(0);

	player_l->Send(packet_l);
	return NULL;
}
