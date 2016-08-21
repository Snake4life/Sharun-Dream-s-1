#include "Sharun.hpp"

void* S_AVAILABLE_EVENT_MATCHING_LIST_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_AVAILABLE_EVENT_MATCHING_LIST, 54);

	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_4(0);

	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_4(0);

	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_4(0);

	packet_l->write_4(0x00010000);
	packet_l->write_2(0);

	player_l->Send(packet_l);
	return NULL;
}
