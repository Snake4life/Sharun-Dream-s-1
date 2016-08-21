#include "Sharun.hpp"

void* S_ABNORMALITY_BEGIN_f(const void** argv)
{
	player*	player_l = (player*) argv[0];
	player*	player_t = (player*) argv[1];
	npc*	npc_t = (npc*) argv[2];
	uint*	id1 = (uint*) argv[3];
	uint*	id2 = (uint*) argv[4];
	packet*	packet_l = new_packet(S_ABNORMALITY_BEGIN, 32);

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);

	if (npc_t) {
		packet_l->write_4(npc_t->Id);
		packet_l->write_4(npc_t->SUBID);
	} else if (player_t) {
		packet_l->write_4(player_t->Id);
		packet_l->write_4(player_t->SUBID);
	} else {
		packet_l->write_4(0);
		packet_l->write_4(0);
	}

	packet_l->write_4(*id1);
	packet_l->write_4(*id2);

	packet_l->write_4(0);
	packet_l->write_4(1);

	player_l->Send(packet_l);
	return NULL;
}
