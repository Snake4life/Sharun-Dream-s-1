#include "Sharun.hpp"

void* S_ATTENDANCE_EVENT_REWARD_COUNT_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_ATTENDANCE_EVENT_REWARD_COUNT, 4);

	packet_l->write_4(8);

	player_l->Send(packet_l);
	return NULL;
}
