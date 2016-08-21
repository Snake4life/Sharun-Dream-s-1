#include "Sharun.hpp"

void* S_PLAYER_CHANGE_ALL_PROF_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_PLAYER_CHANGE_ALL_PROF, 16);

	packet_l->write_2(350);
	packet_l->write_2(350);
	packet_l->write_2(0);
	packet_l->write_2(302);
	packet_l->write_2(5);
	packet_l->write_2(5);
	packet_l->write_2(5);
	packet_l->write_2(5);

	player_l->Send(packet_l);
	return NULL;
}
