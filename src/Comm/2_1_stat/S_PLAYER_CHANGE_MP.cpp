#include "Sharun.hpp"

void* S_PLAYER_CHANGE_MP_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	player*	attacker1 = (player*)argv[1];
	npc*	attacker2 = (npc*)argv[2];
	int*	countChange = (int*)argv[3];
	int*	type = (int*)argv[4];
	packet* packet_l = new_packet(S_PLAYER_CHANGE_MP, 32);

	packet_l->write_4(player_l->Stats.MP); // сколько сейчас
	packet_l->write_4(player_l->Stats.maxMP[1]); // сколько размер полоски
	packet_l->write_4(*countChange); // на сколько увеличилось хп
	packet_l->write_4(*type);// если 01 будет зелёный плюсик
	packet_l->write_4(player_l->Id); // наш ид
	packet_l->write_4(player_l->SUBID); // наш сабид
	if(attacker1 || attacker2) {
		packet_l->write_4(attacker1 ? attacker1->Id : attacker2->npc_id); // ИД того кто вас хильнул
		packet_l->write_4(attacker1 ? attacker1->SUBID : attacker2->SUBID); // САБ ИД того кто вас хильнул
	} else {
		packet_l->write_4(0); // ИД того кто вас хильнул
		packet_l->write_4(0); // САБ ИД того кто вас хильнул
	}

	player_l->Send(packet_l);
	return NULL;
}
