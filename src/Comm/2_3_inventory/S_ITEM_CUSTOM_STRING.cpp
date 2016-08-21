#include "Sharun.hpp"

void* S_ITEM_CUSTOM_STRING_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_ITEM_CUSTOM_STRING, 12);

	packet_l->write_4(0);
	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);

	player_l->Send(packet_l);
	return NULL;
}
