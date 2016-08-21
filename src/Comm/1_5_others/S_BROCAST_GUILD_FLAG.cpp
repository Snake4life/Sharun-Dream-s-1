#include "Sharun.hpp"

void* S_BROCAST_GUILD_FLAG_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_BROCAST_GUILD_FLAG, 1);

	packet_l->write_1(0);

/*
 * 2 count
 * 2 1st pos
 * [loop]
 * 	2 this pos
 * 	2 next pos
 * 	4 ID ?
 * 	S File Name ?
 * [/loop]
 */
	player_l->Send(packet_l);
	return NULL;
}
