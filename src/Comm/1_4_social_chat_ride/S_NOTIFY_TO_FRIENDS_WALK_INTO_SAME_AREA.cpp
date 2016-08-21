#include "Sharun.hpp"

void* S_NOTIFY_TO_FRIENDS_WALK_INTO_SAME_AREA_f(const void** argv)
{
	player*	player_l1 = (player*)argv[0];
	player*	player_l2 = (player*)argv[1];

	packet* packet_l = new_packet(S_NOTIFY_TO_FRIENDS_WALK_INTO_SAME_AREA, 20);

	packet_l->write_4(player_l1->Id);
	packet_l->write_4(player_l2->Id);
	packet_l->write_4(player_l2->country);	// ZONE DATA 1
	packet_l->write_4(player_l2->lander);	// ZONE DATA 2
	packet_l->write_4(player_l2->aera);	// ZONE DATA 3

	return packet_l;
}
