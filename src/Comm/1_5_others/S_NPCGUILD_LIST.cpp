#include "Sharun.hpp"

void* S_NPCGUILD_LIST_f(const void** argv)
{
	player* player_l = (player*) argv[0];

	uint value[][5] = { 
	  {1, 601, 2, 0, 0},
	  {1, 602, 2, 0, 0},
	  {1, 603, 2, 0, 0},
	  {2, 604, 2, 0, 0},
	  {3, 605, 4, 3500, 405},
	  {9, 610, 6, 0, 0},
	  {5, 901, 5, 6600, 103260},
	  {5, 902, 5, 1500, 8920},
	  {0,0,0,0,0}
	};

	ushort NPCGUILD_Count = 0;
	for (int i=0; value[i][1]; i++)
		NPCGUILD_Count++;

	packet* packet_l = new_packet(S_NPCGUILD_LIST, 12 + NPCGUILD_Count * 24);

	packet_l->write_2(NPCGUILD_Count);
	ushort Next = packet_l->write_NextPos();

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);

	for (int i=0; value[i][1]; i++) {
		packet_l->write_Pos(Next);
		packet_l->write_Pos(0);
		Next = packet_l->write_NextPos();

		packet_l->write_4(value[i][0]);
		packet_l->write_4(value[i][1]);
		packet_l->write_4(value[i][2]);
		packet_l->write_4(value[i][3]);
		packet_l->write_4(value[i][4]);
	}
/*
	packet* packet_l = new_packet(S_NPCGUILD_LIST, 12);
	packet_l->write_4(0);
	packet_l->write_4(0x0FAC2722);
	packet_l->write_4(0x00008000);
*/
	player_l->Send(packet_l);
	return NULL;
}
