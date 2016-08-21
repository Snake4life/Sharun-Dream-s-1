#include "Sharun.hpp"
/*
enum S_DESPAWN_NPC_EFFECT {
	S_DESPAWN_NPC_DISAPPEARS = 1,
	S_DESPAWN_NPC_DISAPPEARS_DUST = 4,
	S_DESPAWN_NPC_DEAD = 5
}
*/
void* S_DESPAWN_NPC_f(const void** argv)
{
	player*	player_l = (player*)argv[0];
	npc*	npc_l = (npc*)argv[1];
	packet* packet_l = new_packet(S_DESPAWN_NPC, 29);
//	  player_t *player_l, NPC_t *npc)

		if (npc_l) {
			packet_l->write_4(npc_l->Id);
			packet_l->write_4(npc_l->SUBID);
		} else {
			packet_l->write_4(player_l->Id);
			packet_l->write_4(player_l->SUBID);
		}

		for (int i=0; i<3; i++) {
			if (npc_l)
				packet_l->write_F(npc_l->World.XYZ[i]);
			else
				packet_l->write_F(player_l->DjW->XYZ[i]);
		}

		packet_l->write_1(1); // S_DESPAWN_NPC_EFFECT

		packet_l->write_4(0);
		packet_l->write_4(0);

	return packet_l;
}
