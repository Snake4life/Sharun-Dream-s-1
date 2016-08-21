#include "Sharun.hpp"

void* S_USER_ITEM_EQUIP_CHANGER_f(const void** argv)
{
	player* player_l = (player*) argv[0];

	uint value[] = {1, 3, 4, 5, 6, 7, 8, 9, 10, 11, 19, 20, 0};

	ushort UIEC_Count = 0;
	for (int i=0; value[i]; i++)
		UIEC_Count++;
	packet* packet_l = new_packet(S_USER_ITEM_EQUIP_CHANGER, 12 + UIEC_Count * 12);

	packet_l->write_2(UIEC_Count);
	ushort Next = packet_l->write_NextPos();

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);

	for (int i=0; value[i]; i++) {
		packet_l->write_Pos(Next);
		packet_l->write_Pos(0);
		Next = packet_l->write_NextPos();

		packet_l->write_4(value[i] - 2);
		packet_l->write_4(0);
	}

	player_l->Send(packet_l);
	return NULL;
}
