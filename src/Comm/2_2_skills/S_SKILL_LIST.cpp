#include "Sharun.hpp"

void* S_SKILL_LIST_f(const void** argv)
{
	player* player_l = (player*)argv[0];

	ushort Count = 0;
	for (int j=0; j<50; j++)
	{
		if (player_l->skill[j].level)
			Count++;
	}
	skill_2_t *skill2 = player_l->skill2;
	while (skill2)
	{
		skill2 = skill2->next;
		Count++;
	}

	packet* packet_l = new_packet(S_SKILL_LIST, 4 + Count * 10);

	ushort last = 0;
	packet_l->write_2(Count);
	last = packet_l->write_NextPos();

	for (int j=0; j<50; j++)
	{
		if (player_l->skill[j].level) {
			packet_l->write_Pos(last);

			packet_l->write_Pos(0);
			last = packet_l->write_NextPos();

			packet_l->write_4(player_l->skill[j].id*10000 + player_l->skill[j].level*100 + player_l->skill[j].type);
			packet_l->write_2(1); // active
		}
	}

	skill2 = player_l->skill2;
	while (skill2)
	{
		packet_l->write_Pos(last);

		packet_l->write_Pos(0);
		last = packet_l->write_NextPos();

		packet_l->write_4(skill2->id);
		packet_l->write_2(skill2->type); // active
		skill2 = skill2->next;
	}

	player_l->Send(packet_l);
	return NULL;
}
