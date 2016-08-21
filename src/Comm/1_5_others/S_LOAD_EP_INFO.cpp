#include "Sharun.hpp"

void* S_LOAD_EP_INFO_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_LOAD_EP_INFO, 8 * 5);

	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);
	packet_l->write_8(0);

	player_l->Send(packet_l);
	return NULL;
}
