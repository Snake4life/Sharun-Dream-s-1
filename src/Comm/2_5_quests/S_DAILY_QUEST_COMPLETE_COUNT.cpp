#include "Sharun.hpp"

void* S_DAILY_QUEST_COMPLETE_COUNT_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_DAILY_QUEST_COMPLETE_COUNT, 5);

	// Actual
	packet_l->write_2(0);
	// Max
	packet_l->write_2(10);

	packet_l->write_1(0);

	player_l->Send(packet_l);
	return NULL;
}
