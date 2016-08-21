#include "Sharun.hpp"

void* S_LOGIN_ARBITER_f(const void** argv)
{
	player* player_l = (player*)argv[0];
	uchar* result = (uchar*)argv[1];
	packet* packet_l = new_packet(S_LOGIN_ARBITER, 19);

	switch (*result) {
		case 2: // All ready logged
			packet_l->write_2(0);
			packet_l->write_2(262);
			packet_l->write_4(32768);
			packet_l->write_4(0);
			break;
		case 1: // Ok !
			packet_l->write_2(1);
			packet_l->write_2(2);
			packet_l->write_4(0);
			packet_l->write_2(0);
			packet_l->write_2(6);
			break;
		default: // will close Client
			packet_l->write_2(0);
			packet_l->write_2(257);
			packet_l->write_4(32768);
			packet_l->write_4(0);
	}
	packet_l->write_4(0);
	packet_l->write_2(0);
	packet_l->write_1(0);

	player_l->Send(packet_l);
	return NULL;
}
