#include "Sharun.hpp"

void* S_SPAWN_ME_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_SPAWN_ME, 24);

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);
	for (int i=0; i<3; i++)
		packet_l->write_F(player_l->DjW->XYZ[i]);
	packet_l->write_2(player_l->DjW->heading);
	packet_l->write_2(player_l->Stats.HP ? 1 : 0);

	player_l->Send(packet_l);

	player_l->Spawn->is = 1;
	return NULL;
}
