#include "Sharun.hpp"

void* S_SIMPLE_TIP_REPEAT_CHECK_f(const void** argv)
{
	player*	player_l = (player*)argv[0];
//	uint*	va = (uint*)argv[1];
	packet* packet_l = new_packet(S_SIMPLE_TIP_REPEAT_CHECK, 5);

//	packet_l->write_4(*va);
	packet_l->write_4(0);
	packet_l->write_1(0);

	player_l->Send(packet_l);
	return NULL;
}
