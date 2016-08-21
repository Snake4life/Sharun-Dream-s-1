#include "Sharun.hpp"

void* S_STR_EVALUATE_LIST_f(const void** argv)
{
	player*	player_l = (player*) argv[0];
	uint*	type = (uint*) argv[1];
	char16_t*	name = (char16_t*) argv[2];
	packet* packet_l = new_packet(S_STR_EVALUATE_LIST, 4 + 14 + strlen16_bin(name));

	packet_l->write_2(1);	// count
	ushort Next = packet_l->write_NextPos(); // 1st pos

// [loop]
	packet_l->write_Pos(Next);
	packet_l->write_Pos(0);
	packet_l->write_2(0);

	ushort name_pos = packet_l->write_NextPos();

	packet_l->write_4(*type);//индекс
	packet_l->write_4(0); //18

	packet_l->write_Pos(name_pos);
	packet_l->write_S(name);
// [/loop]

	player_l->Send(packet_l);
	return NULL;
}
