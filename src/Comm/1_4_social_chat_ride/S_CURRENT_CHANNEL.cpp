#include "Sharun.hpp"

void* S_CURRENT_CHANNEL_f(const void** argv)
{
	short i = 0;
	player*	player_l = (player*)argv[i++];
	packet* packet_l = new_packet(S_CURRENT_CHANNEL, 12);

	packet_l->write_4(player_l->DjW->Zone->Id);
	packet_l->write_4(1);
	packet_l->write_4(0);

	player_l->Send(packet_l);

	return packet_l;
}
