#include "Sharun.hpp"

void* S_SYSTEM_MESSAGE_f(const void** argv)
{
	player*		player_l = (player*) argv[0];
	const char16_t*	value1 = (char16_t*) argv[1];
	const char16_t*	value2 = (char16_t*) argv[2];
	packet* packet_l = new_packet(S_SYSTEM_MESSAGE, 2 + strlen16_bin(value1) + ( value2 ? strlen16_bin(value2) : 0));

	packet_l->write_2(6);
	packet_l->write_S(value1);
	if (value2) {
		packet_l->pos -= 2;
		packet_l->size -= 2;
		packet_l->write_S(value2);
	}

	player_l->Send(packet_l);
	return NULL;
}
