#include "Sharun.hpp"

void* S_LOAD_TOPO_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_LOAD_TOPO, 17);

	packet_l->write_4(player_l->DjW->Zone->Id);

	for (int i=0; i<3; i++)
		packet_l->write_F(player_l->DjW->XYZ[i]);

	packet_l->write_1(0);

	player_l->Send(packet_l);

//	*player_l->Still_Online = -1;
	return NULL;
}

