#include "Sharun.hpp"

void* S_ANNOUNCE_MESSAGE_f(const void** argv)
{
	short i = 0;
	player*	player_l = (player*)argv[i++];
	packet* packet_l = new_packet(S_ANNOUNCE_MESSAGE, 4);

	packet_l->write_4(3416);

	player_l->Send(packet_l);

	return packet_l;
}
