#include "Sharun.hpp"

void* S_EQUIP_ITEM_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	ulong*	item_id = (ulong*) argv[0];
	packet* packet_l = new_packet(S_EQUIP_ITEM, 16);

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);
	packet_l->write_8(*item_id);

	player_l->Send(packet_l);
	return NULL;
}
