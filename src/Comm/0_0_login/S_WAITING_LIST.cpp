#include "Sharun.hpp"

void* S_WAITING_LIST_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_WAITING_LIST, 4*4);

	// DONT WORK ... :'(

	packet_l->write_4(100);
	packet_l->write_4(100);
	packet_l->write_4(100);
	packet_l->write_4(100);

	player_l->Send(packet_l);
	return NULL;
}

