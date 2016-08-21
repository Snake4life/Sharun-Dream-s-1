#include "Sharun.hpp"

void* S_ABNORMALITY_END_f(const void** argv)
{
	player*	player_l = (player*) argv[0];
	uint*	id1 = (uint*) argv[1];
	packet*	packet_l = new_packet(S_ABNORMALITY_END, 12);

	packet_l->write_4(player_l->Id);
	packet_l->write_4(player_l->SUBID);

	packet_l->write_4(*id1);

	player_l->Send(packet_l);
	return NULL;
}
