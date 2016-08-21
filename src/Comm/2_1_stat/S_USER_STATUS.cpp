#include "Sharun.hpp"

void* S_USER_STATUS_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_USER_STATUS, 13);

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);
	packet_l->write_4(0);
	packet_l->write_1(0);

	player_l->Send(packet_l);
	return NULL;
}
