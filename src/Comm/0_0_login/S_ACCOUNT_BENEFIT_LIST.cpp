#include "Sharun.hpp"

void* S_ACCOUNT_BENEFIT_LIST_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_ACCOUNT_BENEFIT_LIST, 6);

	packet_l->write_4(0);
	packet_l->write_1(0);

	player_l->Send(packet_l);
	return NULL;
}
