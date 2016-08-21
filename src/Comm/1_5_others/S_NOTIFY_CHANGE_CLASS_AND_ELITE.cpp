#include "Sharun.hpp"

void* S_NOTIFY_CHANGE_CLASS_AND_ELITE_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_NOTIFY_CHANGE_CLASS_AND_ELITE, 8);

	packet_l->write_8(0);

	player_l->Send(packet_l);
	return NULL;
}
