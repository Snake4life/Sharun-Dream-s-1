#include "Sharun.hpp"

void* S_CAN_CREATE_USER_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_CAN_CREATE_USER, 4);

	if (player_l->Characters_Count < player_l->Characters_Max)
		packet_l->write_4(1);
	else
		packet_l->write_4(0);

	player_l->Send(packet_l);
	return NULL;
}
