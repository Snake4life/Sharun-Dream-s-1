#include "Sharun.hpp"

void* S_CONFIRM_INVITE_CODE_BUTTON_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_CONFIRM_INVITE_CODE_BUTTON, 13);

/*
	// At added Gunner
	packet_l->write_2(15);
	packet_l->write_2(64001);
	packet_l->write_2(17041);
	packet_l->write_2(86);
*/
	// At added Ninja
	packet_l->write_2(15);
	packet_l->write_2(9217);
	packet_l->write_2(43630);
	packet_l->write_2(87);


	packet_l->write_4(0);
	packet_l->write_1(0);

	Send_Packet(player_l, packet_l);
	return NULL;
}
