#include "Sharun.hpp"

void* S_CREATE_USER_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	uchar* result = (uchar*)argv[1];
	packet* packet_l = new_packet(S_CREATE_USER, 1);

	packet_l->write_1(*result);

	player_l->Send(packet_l);
	return NULL;
}
