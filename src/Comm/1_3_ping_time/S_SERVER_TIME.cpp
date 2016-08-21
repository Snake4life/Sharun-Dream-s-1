#include "Sharun.hpp"

void* S_SERVER_TIME_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_SERVER_TIME, 8);

	packet_l->write_8(time(NULL));

	player_l->Send(packet_l);
	return NULL;
}
