#include "Sharun.hpp"

void* S_UPDATE_CONTENTS_ON_OFF_f(const void** argv)
{
	ushort value[] = {2, 3, 4, 8, 9, 0};

	player* player_l = (player*)argv[0];
	packet* packet_l = NULL;
	
	for (uchar i=0; value[i]; i++) {
		packet_l = new_packet(S_UPDATE_CONTENTS_ON_OFF, 5);
		packet_l->write_4(value[i]);
		packet_l->write_1(0);
		player_l->Send(packet_l);
	}
	return NULL;
}
