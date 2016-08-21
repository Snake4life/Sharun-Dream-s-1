#include "Sharun.hpp"

void* S_SOCIAL_CANCEL_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_SOCIAL_CANCEL, 8);

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);

	return packet_l;
}
