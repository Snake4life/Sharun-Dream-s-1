#include "Sharun.hpp"

void* S_CURRENT_ELECTION_STATE_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_CURRENT_ELECTION_STATE, 22);

	packet_l->write_4(0);
	packet_l->write_4(5);
	packet_l->write_4(0);

	packet_l->write_2(0);

	packet_l->write_1(5);
	packet_l->write_1(61);
	packet_l->write_1(228);
	packet_l->write_1(81);

	packet_l->write_2(0);

	packet_l->write_2(0);
/*
	packet_l->write_4(0);
	packet_l->write_4(11);
	packet_l->write_4(0);
	packet_l->write_4(0x3CFF0000);
	packet_l->write_4(0x000051E4);
	packet_l->write_2(0);
*/
	player_l->Send(packet_l);
	return NULL;
}
