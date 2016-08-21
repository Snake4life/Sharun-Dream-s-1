#include "Sharun.hpp"

void* S_CANCEL_EXIT_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_CANCEL_EXIT, 1);

	player_l->exit_type = 0;

	packet_l->write_1(0);

	player_l->Send(packet_l);
	return NULL;
}
