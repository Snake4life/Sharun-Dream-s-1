#include "Sharun.hpp"

void* S_FESTIVAL_LIST_f(const void** argv)
{
	player* player_l = (player*) argv[0];

	uint value[] = {1, 2, 3, 0};
//	uint value[] = {4, 80, 0};

	ushort Festival_Count = 0;
	for (int i=0; value[i]; i++)
		Festival_Count++;

	packet* packet_l = new_packet(S_FESTIVAL_LIST, 4 + Festival_Count * 8);

	packet_l->write_2(Festival_Count);
	ushort Next = packet_l->write_NextPos();

	for (int i=0; value[i]; i++) {
		packet_l->write_Pos(Next);
		packet_l->write_Pos(0);
		Next = packet_l->write_NextPos();

		packet_l->write_4(value[i]);	// Festival ID
	}

	player_l->Send(packet_l);
	return NULL;
}
