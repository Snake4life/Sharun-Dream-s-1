#include "Sharun.hpp"

void* S_F2P_PremiumUser_Permission_f(const void** argv)
{
	player* player_l = (player*) argv[0];
	packet* packet_l = new_packet(S_F2P_PremiumUser_Permission, 24);

	packet_l->write_2(1);
	packet_l->write_2(20);

	packet_l->write_4(5);

	packet_l->write_F(1);
	packet_l->write_F(1);

	packet_l->write_4(20);
	packet_l->write_4(1);

	player_l->Send(packet_l);
	return NULL;
}
