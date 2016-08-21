#include "Sharun.hpp"

void* S_ARTISAN_SKILL_LIST_f(const void** argv)
{
	player* player_l = (player*) argv[0];

	uint value[] = {6, 7, 21, 22, 23, 0};
	ushort Artisan_Skill_Count = 0;
	for (int i=0; value[i]; i++)
		Artisan_Skill_Count++;

	packet* packet_l = new_packet(S_ARTISAN_SKILL_LIST, 21 + Artisan_Skill_Count * 32);

	packet_l->write_2(Artisan_Skill_Count);
	ushort Next = packet_l->write_NextPos();

	packet_l->write_4(0);
	packet_l->write_4(0);
	packet_l->write_2(0);
	packet_l->write_2(18432);
	packet_l->write_2(3652);
	packet_l->write_2(0);
	packet_l->write_1(0);

	for (int i=0; value[i]; i++) {
		packet_l->write_Pos(Next);
		packet_l->write_Pos(0);
		Next = packet_l->write_NextPos();

		packet_l->write_4(value[i]);
		packet_l->write_4(value[i]);
		packet_l->write_2(0);
		packet_l->write_2(16256);
		packet_l->write_4(-1);
		packet_l->write_4(1);
		packet_l->write_4(-1);
		packet_l->write_4(0);
	}

	player_l->Send(packet_l);
	return NULL;
}
