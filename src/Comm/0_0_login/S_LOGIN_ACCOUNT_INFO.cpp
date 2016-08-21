#include "Sharun.hpp"

void* S_LOGIN_ACCOUNT_INFO_f(const void** argv)
{
	const char16_t *value = u"PlanetLT";

	player* player_l = (player*)argv[0];
	packet* packet_l = new_packet(S_LOGIN_ACCOUNT_INFO, 10 + strlen16_bin(value));

	ushort pos = packet_l->write_NextPos();

	packet_l->write_4(6175819);
	packet_l->write_4(0);
/*

	packet_l->write_2(19260);
	packet_l->write_1(0);

	ushort pos = packet_l->write_NextPos();
	packet_l->write_2(0);
	packet_l->write_2(5);
	packet_l->write_1(0);
*/
	packet_l->write_Pos(pos);
	packet_l->write_S(value);

	player_l->Send(packet_l);
	return NULL;
}
