#include "Sharun.hpp"

void* S_SPAWN_NPC_f(const void** argv)
{
	player*	player_l = (player*)argv[0];
	npc*	NPC = (npc*)argv[1];
	bool*	isFriend = (bool*)argv[2];
	packet* packet_l = new_packet(S_SPAWN_NPC, 120);

	packet_l->write_4(0);//00 00 00 00 8

	int shiftreplace = packet_l->pos;

	packet_l->write_2(109);// 6D 00 10
	packet_l->write_4(NPC->Id);// A3 D4 0C 00 обжект ид 14
	packet_l->write_4(NPC->SUBID);// 00 80 0B 00 саб ид 18
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00 26

	for (int i=0; i<3; i++)
		packet_l->write_F(NPC->World.XYZ[i]);
	packet_l->write_2(NPC->World.heading);// 10 17 heading 40

	packet_l->write_4(12);// 0C 00 00 00 статик 44

	packet_l->write_4(NPC->npc_id);// 66 00 00 00 нпц темплейт ид 48
	packet_l->write_2(NPC->npc_type);// 0D 00 класс моба 50

	packet_l->write_2(0);// 2D 00 мб расса моба 52
	packet_l->write_4(110);// 4C 00 00 00 56
	packet_l->write_2(0);// 00 00 58
	packet_l->write_4(5);// 05 00 00 00 62
	packet_l->write_1(1);// 01 00 видимость 63

	packet_l->write_1(*isFriend);// 01 00 1 - нпс 0 - моб 64
	packet_l->write_2(NPC->spawned); // нужна ли вспышка 0 -вспышка

	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_8(0);// 00 00 00 00 00 00 00 00
	packet_l->write_2(0);// 00 00
	packet_l->write_1(0);// 00
	packet_l->write_4(0);// new 00000000
	packet_l->write_1(0);// new 00

	packet_l->write_Pos(shiftreplace);
	packet_l->write_4(0xB9ACC5D8);// new D8C5ACB9
	packet_l->write_4(0x0000CE74);// new 74CE0000

	player_l->Send(packet_l);
	return NULL;
}
