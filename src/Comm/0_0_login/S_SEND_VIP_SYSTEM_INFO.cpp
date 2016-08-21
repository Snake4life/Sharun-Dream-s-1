#include "Sharun.hpp"

void* S_SEND_VIP_SYSTEM_INFO_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_SEND_VIP_SYSTEM_INFO, 43);

	ushort pos = packet_l->write_NextPos();
	packet_l->write_2(1);

	packet_l->write_4(0);
	packet_l->write_2(0);
	packet_l->write_1(0);

	packet_l->write_4(1000);

	packet_l->write_8(0);

	packet_l->write_2(3585);
	packet_l->write_2(27);

	packet_l->write_8(0);
	packet_l->write_4(0);
	packet_l->write_1(0);

	packet_l->write_1(1);

	packet_l->write_Pos(pos);
	packet_l->write_2(0);

	player_l->Send(packet_l);
	return NULL;
}
