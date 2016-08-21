#include "Sharun.hpp"

void* S_PET_INCUBATOR_INFO_CHANGE_f(const void** argv)
{
	player* player_l = (player*) argv[0];

	uint value[] = {3, 2, 2, 2, 2, 0};

	ushort Pet_Incubator_Count = 0;
	for (int i=0; value[i]; i++)
		Pet_Incubator_Count++;
	packet* packet_l = new_packet(S_PET_INCUBATOR_INFO_CHANGE, 18 + Pet_Incubator_Count * 12);

	packet_l->write_2(Pet_Incubator_Count);
	ushort Next = packet_l->write_NextPos();

	packet_l->write_4(1);
	packet_l->write_4(0);
	packet_l->write_4(60);
	packet_l->write_2(0);

	for (int i=0; value[i]; i++) {
		packet_l->write_Pos(Next);
		packet_l->write_Pos(0);
		Next = packet_l->write_NextPos();

		packet_l->write_4(value[i] - 3);
		packet_l->write_4(0);
	}

	player_l->Send(packet_l);
	return NULL;
}
