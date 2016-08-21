#include "Sharun.hpp"

void* C_SHOW_ITEM_TOOLTIP_EX_f(player* player_l, packet* packet_l)
{
	ushort namePos = packet_l->read_2();

	packet_l->read_2();
	packet_l->read_2();
	
	ulong itemID = packet_l->read_8();

	const char16_t* name;
	name = (char16_t*) packet_l->read_D(namePos);

	const void *args[] = {player_l, name, &itemID, NULL};
	Sharun->OpCodes.Send[S_SHOW_ITEM_TOOLTIP](args);

	return NULL;
}
