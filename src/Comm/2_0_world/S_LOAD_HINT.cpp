#include "Sharun.hpp"

void* S_LOAD_HINT_f(const void** argv)
{
	player* player_l = (player*)argv[0];
//	uint value[] = {2, 7, 1, 202, 5, 0};
	uint value[] = {0};

	ushort Hint_Count = 0;
	for (int i=0; value[i]; i++)
		Hint_Count++;
	packet* packet_l = new_packet(S_LOAD_HINT, 4 + Hint_Count * 12);

	packet_l->write_2(Hint_Count);
	ushort Next = packet_l->write_NextPos();

	for (int i=0; value[i]; i++) {
		packet_l->write_Pos(Next);
		packet_l->write_Pos(0);
		Next = packet_l->write_NextPos();

		packet_l->write_4(23);
		packet_l->write_4(value[i]);
	}

	player_l->Send(packet_l);
	return NULL;
}
